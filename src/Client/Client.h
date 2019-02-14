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

	std::string ipAddress;
	int port;

	char buf[4096];
	std::string returnMessage = "";

	int number = 0;

	std::vector<int> m_joiners;
	std::vector<int> m_leavers;

	Packet p;

private:
	
};
#endif // !CLIENT_H

