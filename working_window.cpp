#include "working_window.h"
#include "ui_working_window.h"
#include <iostream>

WorkingWindow::WorkingWindow(ClientConnection* p_connection, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::WorkingWindow),
	m_connection(p_connection)
{
	ui->setupUi(this);
}

void WorkingWindow::update_position_in_queue(int p_pos)
{
	QString text = "Pozycja w kolejce: ";
	
	if (p_pos != -1)
	{
		text.append(std::to_string(p_pos+1).c_str());
	}
	else
	{
		text.append("Stanowisko nie w kolejce");
	}
	
	ui->LabelPositionInQueue->setText(text);
}

WorkingWindow::~WorkingWindow()
{
	delete ui;
}

void WorkingWindow::on_ButtonFree_clicked()
{
	if (slot_status != SlotStatus::FREE)
	{
		//wysyłanie powiadomienia o wolnym stanowisku
		std::string text = "status;0"; 
		
		text = m_connection->send_data(text.c_str());
		
		std::clog<<"Odebrano: "<<text<<std::endl;
		
		slot_status = SlotStatus::FREE; //aby dwukrotnie nie wciskać tego samego przycisku
	}
}

void WorkingWindow::on_ButtoBusy_clicked()
{
	if (slot_status != SlotStatus::BUSY)
	{
		//wysyłanie powiadomienia o wolnym stanowisku
		std::string text = "status;1"; 
		
		text = m_connection->send_data(text.c_str());
		
		std::clog<<"Odebrano: "<<text<<std::endl;
		
		slot_status = SlotStatus::BUSY; //aby dwukrotnie nie wciskać tego samego przycisku
	}
}

void WorkingWindow::on_ButtonBreak_clicked()
{
	if (slot_status != SlotStatus::BREAK)
	{
		//wysyłanie powiadomienia o wolnym stanowisku
		std::string text = "status;2"; 
		
		text = m_connection->send_data(text.c_str());
		
		std::clog<<"Odebrano: "<<text<<std::endl;
		
		slot_status = SlotStatus::BREAK; //aby dwukrotnie nie wciskać tego samego przycisku
	}
}

void WorkingWindow::on_ButtonExit_clicked()
{
    this->close();
}
