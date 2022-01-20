#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H
#include <winsock2.h>
#include <QtCore>
#include "mainwindow.h"

class ServerConnection : public QThread
{
    public:
		ServerConnection(MainWindow* p_window); //lokalny adres IP oraz domyĹ›lny port
		ServerConnection(const int& p_port, int p_max_clients, MainWindow* p_window); //lokalny adres IP z wybranym portem
		~ServerConnection();
		void config(const int& p_port, int p_max_clients);
		void run();
		
	private:
		const char* m_IP_address; //adres IP gdzie ma byÄ‡ postawiony serwer
		const int m_port; //port na ktĂłrym ma byÄ‡ postawiony serwer
		
		WSADATA m_wsa_data; //dane wersji winsocka
		SOCKET m_server; //wskaĹşnik na serwer
		SOCKET* m_clients; //klienci podĹ‚Ä…czeni do serwera
		SOCKADDR_IN m_address; //struktura przechowujÄ…ca dane poĹ‚Ä…czenia
		
		fd_set master;
		fd_set tmp_master;
		
		char* get_local_IP(); //funkcja zwracajÄ…ca lokalne IP komputera
		void handle_client(SOCKET client, char* data, int data_len);
		
		MainWindow* m_window;
};

#endif // SERVER_CONNECTION_H
