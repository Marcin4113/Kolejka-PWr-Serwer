#include "main_window.h"
#include "client_connection.h"
#include "working_window.h"
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) : 
	QMainWindow(parent), 
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	this->setFixedSize(this->size());
	ui->ButtonNext->setDisabled(true);
	
	workplace_number = 2;
}

MainWindow::~MainWindow()
{
	delete ui;
}

QListWidgetItem* MainWindow::add_elem(const char* str)
{
	QListWidget* list = ui->listWidget;
	
	list->addItem(str); //dodanie elementu do listy
	
	QListWidgetItem* item = list->item(list->count()-1);
	
	item->setTextAlignment(Qt::AlignCenter); //wyśrodkowanie tekstu
	
	return item;
}

void MainWindow::disable_elem(QListWidgetItem* item)
{
	item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
}

void MainWindow::set_connection_object(ClientConnection* p_connection)
{
	m_connection = p_connection;
}

void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{
	ui->ButtonNext->setDisabled(false);
}

void MainWindow::on_ButtonNext_clicked()
{
	std::string text = ui->listWidget->currentItem()->text().toStdString();
	text.erase(0, text.find(".")+2);
	
	//wysyłanie powiadomienia o logowaniu do stanowiska
	text = "login;" + std::to_string(std::atoi(text.c_str())) + ";" + std::to_string(workplace_number) + ";";
	std::cout<<"'"<<text<<"'"<<std::endl;
	
	text = m_connection->send_data(text.c_str());
	
	std::cout<<"Odebrano: "<<text<<std::endl;
	
	if (text.compare("OK") == 0)
	{
		WorkingWindow work_window(m_connection, this);
		m_connection->run_receive_data(); //uruchomienie wątku do odbioru danych pozycji w kolejce
		m_connection->set_working_window(&work_window); //ustawiamy adres do drugiego okna, aby aktualizować pozycję w kolejce
		this->close();
		work_window.exec();
	}
}

void MainWindow::on_ButtonExit_clicked()
{
    this->close();
}

void MainWindow::load_workplace_number()
{
	std::fstream file("..\\data\\properties.conf", std::ios::in);
	
	if (file.good())
	{
		std::string line;
		
		while(!file.eof())
		{
			std::getline(file, line);
			
			//jeżeli linia nie zaczyna się od komentarza i nie jest pusta
			if (line[0] != '#' && line != "")
			{
				unsigned int pos;
				
				if ((pos = line.find("workplace_number")) != std::string::npos)
				{
					line = line.substr(pos + strlen("workplace_number") + 1, line.length());
					
					workplace_number = std::atof(line.c_str());
				}
			}
		}
	}
}
