#include "mainwindow.h"
#include <QApplication>
#include "server_connection.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
	ServerConnection connection(&window);
	
    window.show();
	connection.start();
	
	int status = app.exec();
	//zakończenie działania wątku z połączeniem
	connection.terminate();
	
    return status;
}
