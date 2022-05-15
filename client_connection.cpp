#include "client_connection.h"
#include "main_window.h"
#include <iostream>
#include <string>
#include <fstream>

ClientConnection::ClientConnection(char *p_IP_address, const int &p_port, MainWindow* p_window) :
	//m_IP_address(p_IP_address),
	m_port(p_port),
	m_window(p_window)
{
	int status;
	
	std::clog<<"Starting up winsock... ";
	
	//uruchomienie winsocka
	if (WSAStartup(MAKEWORD(2, 1), &m_wsa_data) != 0)
	{
		std::cerr<<"Error while starting winsock! (WSAStartup())"<<std::endl;
		std::cerr<<"Error number: "<<WSAGetLastError()<<std::endl;
		throw std::runtime_error(strcat("WSAStartup() -> ", std::to_string(WSAGetLastError()).c_str()));
	}
	
	std::clog<<"done!"<<std::endl;
	std::clog<<"Setting up client... ";
	
	status = socket(AF_INET, SOCK_STREAM, 0);
	
	if (status == SOCKET_ERROR)
	{
		std::cerr<<"Error - socket()"<<std::endl;
		std::cerr<<"Error number: "<<WSAGetLastError()<<std::endl;
		throw std::runtime_error(strcat("socket() -> ", std::to_string(WSAGetLastError()).c_str()));
	}
	
	m_connection = status;
	
	load_connection_info();
	
	//ustawienie adresu do komunikacji z serwerem
	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = inet_addr(m_IP_address);
	m_address.sin_port = htons(m_port);
	std::clog<<"done!"<<std::endl;
	
	std::clog<<"Server IP: "<<m_IP_address<<std::endl;
	std::clog<<"Server port: "<<m_port<<std::endl;
	std::clog<<"Connecting to the server... ";
	
	while(connect(m_connection, (SOCKADDR*)&m_address, sizeof(m_address)) == SOCKET_ERROR)
	{
		std::cerr<<"Error - connect()"<<std::endl;
		std::cerr<<"Error number: "<<WSAGetLastError()<<std::endl;
		
		int result = MessageBox(NULL, (LPCWSTR)L"Nie mozna sie podlaczyc do serwera!", (LPCWSTR)L"Blad!", MB_RETRYCANCEL);
		
		switch (result)
		{
			case IDCANCEL:
				throw std::runtime_error(strcat("connect() -> ", std::to_string(WSAGetLastError()).c_str()));
				break;
		}
	}
	
	std::clog<<"connected!"<<std::endl;
	
	m_window->set_connection_object(this);
	
	std::cout<<m_connection<<std::endl;
}

ClientConnection::~ClientConnection()
{
	shutdown(m_connection, SD_BOTH);
}

void ClientConnection::set_working_window(WorkingWindow* p_working_window)
{
	m_working_window = p_working_window;
}

void ClientConnection::get_workplaces()
{
	char buf[256];
	memset(buf, 0, sizeof(buf));
	
	send(m_connection, "get status", strlen("get status"), 0);
	
	recv(m_connection, buf, sizeof(buf), 0);
	
	std::clog<<"buf: "<<buf<<std::endl;
	
	char* tmp;
	std::string tmp2;
	QListWidgetItem* item;
	tmp = strtok(buf, ";");
	
	for (;tmp != NULL;)
	{
		tmp2 = "Stanowisko nr. ";
		tmp2 += tmp;
		
		tmp = strtok(NULL, ";");
		
		if (strcmp(tmp, "0") != 0)
		{
			tmp2 += " - Zajęte przez nr. ";
			tmp2 += tmp;
		}
		
		tmp2 += "\n";
		
		item = m_window->add_elem(tmp2.c_str());
		
		if (strcmp(tmp, "0") != 0)
		{
			m_window->disable_elem(item);
		}
		
		
		tmp = strtok(NULL, ";");
	}
}

std::string ClientConnection::send_data(const char* data)
{
	//std::clog<<"mutex locking send_data()"<<std::endl;
	m_recv_mutex.lock();
	//std::clog<<"mutex locked receive_data()"<<std::endl;
	std::cout<<m_connection<<std::endl;
	
	if (send(m_connection, data, strlen(data), 0) > 0)
	{
		#ifdef QT_DEBUG
		
		std::clog<<"Wyslano: '"<<data<<"'"<<std::endl;
		
		#endif
		
		char buf[256];
		memset(buf, 0, 256);
		
		//std::clog<<"mutex unlocking receive_data()"<<std::endl;
		if (recv(m_connection, buf, sizeof(buf), 0) > 0)
		{
			m_recv_mutex.unlock();
			return std::string(buf);
		}
		else
		{
			std::cerr<<"Error - send_data(), recv(), error: "<<WSAGetLastError()<<std::endl;
			m_recv_mutex.unlock();
			return nullptr;
		}
	}
	
	std::cerr<<"Error - send_data(), send(), error: "<<WSAGetLastError()<<std::endl;
	m_recv_mutex.unlock();
	return nullptr;
}

void ClientConnection::run_receive_data()
{
	//uruchom wątek który odbiera dane od serwera
	thread = std::thread(&ClientConnection::receive_data, this);
	thread.detach();
}

void ClientConnection::load_connection_info()
{
	std::fstream file("data\\properties.conf", std::ios::in);
	
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
				
				//adres ip do połączenia
				if ((pos = line.find("ip:")) != std::string::npos)
				{
					line = line.substr(pos + strlen("ip:") + 1, line.length());
					
					strcpy(m_IP_address, line.c_str());
					
					std::clog<<"File address: "<<m_IP_address<<std::endl;
				}
				
				//port do połączenia
				if ((pos = line.find("port:")) != std::string::npos)
				{
					line = line.substr(pos + strlen("port:") + 1, line.length());
					
					m_port = atoi(line.c_str());
					
					std::clog<<"File port: "<<m_port<<std::endl;
				}
			}
		}
		
		file.close();
	}
	else
	{
		std::cerr<<"Can't open file 'properties.conf'! Error: "<<strerror(errno)<<std::endl;
	}
}

void ClientConnection::receive_data()
{
	int ready;
	char buf[256];
	fd_set master, tmp_master;
	timeval time;
	time.tv_sec = 0;
	time.tv_usec = 10;
	
	m_recv_mutex.lock();
	FD_ZERO(&master);
	FD_SET(m_connection, &master);
	m_recv_mutex.unlock();
	
	while(true)
	{
		//std::clog<<"mutex locking receive_data()"<<std::endl;
		m_recv_mutex.lock();
		//std::clog<<"mutex locked receive_data()"<<std::endl;
		
		tmp_master = master;
		
		if ((ready = select(NULL, &tmp_master, NULL, NULL, &time)) == SOCKET_ERROR)
		{
			std::cerr<<"Error - select()"<<std::endl;
			std::cerr<<"Error number: "<<WSAGetLastError()<<std::endl;
			throw std::runtime_error(strcat("select() -> ", std::to_string(WSAGetLastError()).c_str()));
		}
		
		if (ready > 0)
		{
			char* tmp;
			std::clog<<"receive_data() - ready sockets: "<<ready<<std::endl;
			memset(buf, 0, sizeof(buf));
			
			std::clog<<"socket: "<<tmp_master.fd_array[0]<<std::endl;
			
			if (recv(tmp_master.fd_array[0], buf, sizeof(buf), NULL) > 0)
			{
				#ifdef QT_DEBUG
				
				std::clog<<"Received: "<<buf<<std::endl;
				
				#endif
					
				tmp = strtok(buf, ";");
				
				//jeżeli komenda to 'position:'
				if (strcmp(tmp, "position") == 0)
				{
					tmp = strtok(NULL, ";");
					
					m_working_window->update_position_in_queue(std::atoi(tmp));
				}
			}
			else
			{
				std::clog<<"Connection error"<<std::endl;
			}
		}
		
		//std::clog<<"mutex unlocking receive_data()"<<std::endl;
		m_recv_mutex.unlock();
		//std::clog<<"mutex unlocked receive_data()"<<std::endl;
		Sleep(100);
	}
}
