#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H
#include <winsock2.h>
#include <string>
#include <mutex>
#include <thread>

class MainWindow;
class WorkingWindow;

class ClientConnection
{
	public:
		ClientConnection(char* p_IP_address, const int& p_port, MainWindow* p_window);
		~ClientConnection();
		
		//settery
		void set_working_window(WorkingWindow* p_working_window);
		
		//gettery
		void get_workplaces(); //pobiera informacje od serwera o stanowiskach
		
		std::string send_data(const char* data);
		void run_receive_data();
		
	private:
		WSADATA m_wsa_data;
		SOCKET m_connection;
		SOCKADDR_IN m_address;
		
		char m_IP_address[20]; //adres IP serwera
		int m_port; //port do komunikacji z serwerem
		MainWindow* m_window; //potrzebne w celu modyfikacji elementów w oknie
		WorkingWindow* m_working_window; //potrzebne w celu aktualizacji pozycji w kolejce
		
		void load_connection_info(); //pobiera informacje o danych do połączenia
		void receive_data(); //wątek do pobierania danych z serwera
		
		std::mutex m_recv_mutex; //mutex dla odbierania danych od serwera (dla wątku receive_data() oraz innych metod wykorzystujących recv())
		
		std::thread thread;
};

#endif // CLIENT_CONNECTION_H
