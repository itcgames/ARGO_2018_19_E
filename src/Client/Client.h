#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <vector>
#include "Packet.h"
#pragma comment(lib, "ws2_32.lib")

class Client
{
public:
	Client(std::string ip, int port);
	~Client();
	bool run();
	void receive();
	void sendMessage(Packet packet);

	SOCKET sock;
	sockaddr_in hint;

	int m_serverSize = 0;

	std::string ipAddress;
	int port;

	int number = 0;

	std::vector<int> m_joiners;
	std::vector<int> m_leavers;

	Packet p;

	bool m_startGame = false;

	int m_size = 0;

	Packet * packet = new Packet();
private:
	
};
#endif // !CLIENT_H

