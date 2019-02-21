#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <WS2tcpip.h>
#include <vector>
#include <map>
#include "../../src/Client/Packet.h"

using namespace std;

class Server
{
public:
	Server();

	void Bind();

	void loop();

	void close();

private:
	vector<sockaddr_in> m_clients;
	map<int, int> m_players;
	SOCKET in;
	int playerNum = 0;
};
#endif 

