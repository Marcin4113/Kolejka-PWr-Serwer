#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "ui_main_window.h"
#include "working_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ClientConnection;

class MainWindow : public QMainWindow
{
    Q_OBJECT
	public:
		MainWindow(QWidget *parent = nullptr);
		~MainWindow();
		
		QListWidgetItem* add_elem(const char* str); //dodaje element do listy
		void disable_elem(QListWidgetItem* item); //wyłącza element (nie da się klikąć)
		void send_info();
		
		void set_connection_object(ClientConnection* p_connection); //ustawia zmiennÄ… m_connection aby MainWindow wiedziaĹ‚ o poĹ‚Ä…czeniu
	
	private slots:
		void on_listWidget_itemPressed(QListWidgetItem *item);
		
		void on_ButtonExit_clicked();
		
		void on_ButtonNext_clicked();
		
	private:
		int workplace_number;
		
		Ui::MainWindow* ui;
		ClientConnection* m_connection;
		
		void load_workplace_number();
};
#endif // MAIN_WINDOW_H
