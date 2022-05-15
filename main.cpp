#include "client_connection.h"
#include "main_window.h"
#include <QApplication>

/*TODO: ZABEZPIECZYĆ SYTUACJE GDY 
STANOWISKO ZMIENIA STATUS A SERWER JEST WYŁĄCZONY*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	MainWindow window;
	ClientConnection connection("", 0, &window);
	
	connection.get_workplaces();
	
	window.show();
	int status = app.exec();
	
	//zakończenie działania wątku z połączeniem
	//connection.terminate();
	
    return status;
	//return app.exec();
}
