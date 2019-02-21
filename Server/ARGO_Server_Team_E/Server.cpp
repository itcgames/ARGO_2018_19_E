#include "Server.h"

Server::Server() {
	// Structure to store the WinSock version. This is filled in
	// on the call to WSAStartup()
	WSADATA data;

	// To start WinSock, the required version must be passed to
	// WSAStartup(). This server is going to use WinSock version
	// 2 so I create a word that will store 2 and 2 in hex i.e.
	// 0x0202
	WORD version = MAKEWORD(2, 2);

	// Start WinSock
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		// Not ok! Get out quickly
		cout << "Can't start Winsock! " << wsOk;
		return;
	}
	cout << "Started Winsock! " << endl;
}

void Server::Bind() {
	// Create a socket, notice that it is a user datagram socket (UDP)
	in = socket(AF_INET, SOCK_DGRAM, 0);

	// Create a server hint structure for the server
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY; // Us any IP address available on the machine
	serverHint.sin_family = AF_INET; // Address format is IPv4
	serverHint.sin_port = htons(54000); // Convert from little to big endian

	/*int const buff_size = sizeof(struct sockaddr_in);
	setsockopt(in, SOL_SOCKET, SO_RCVBUF, reinterpret_cast<char const *>(&buff_size), sizeof(buff_size));
	*/									// Try and bind the socket to the IP and port
	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}
	cout << "Bound Listening Socket!" << endl;
}

void Server::loop() {
	int clientLength = sizeof(struct sockaddr_in); // The size of the client information
	sockaddr_in client;
	Packet packet;

	// Enter a loop
	while (true)
	{
		ZeroMemory(&client, clientLength); // Clear the client structure
		ZeroMemory(&packet, sizeof(struct Packet)); // Clear the receive buffer

							   // Wait for message
		int bytesIn = recvfrom(in, (char*)&packet, sizeof(struct Packet) + 1, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR) {
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}
		else {
			int port = ntohs(client.sin_port);

			if (m_players[port] == 0) {
				playerNum++;
				Packet * p = new Packet();
				p->message = 1;
				p->playerNum = playerNum;

				m_players[port] = playerNum;
				m_clients.push_back(client);

				cout << "<SERVER> Player: " << playerNum << " at Port: " << port << endl;
				
				int sendOk = sendto(in, (char*)p, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&m_clients[playerNum - 1], sizeof(m_clients[playerNum - 1]));
				if (sendOk == SOCKET_ERROR)
				{
					std::cout << "<SERVER> Error sending message! " << WSAGetLastError() << std::endl;
				}
				p = new Packet();
				p->message = 2;
				p->playerNum = playerNum;
				for (int i = 1; i <= playerNum; i++) {

					if (i != m_players[port]) {
						sendto(in, (char*)p, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&m_clients[i - 1], sizeof(m_clients[i - 1]));
						cout << "<SERVER> Message sent to other client" << endl;
					}
				}
			}
			else {

				for (int i = 1; i <= playerNum; i++)
				{
					if (i != m_players[port])
					{
						int sendOk = sendto(in, (char*)&packet, sizeof(struct Packet) + 1, 0, (LPSOCKADDR)&m_clients[i - 1], sizeof(m_clients[i - 1]));
						if (sendOk == SOCKET_ERROR)
						{
							std::cout << "<SERVER> Error sending message! " << WSAGetLastError() << std::endl;
						}
						else
						{
							char sendIp[256];
							ZeroMemory(&sendIp, 256);
							inet_ntop(AF_INET, &m_clients[i - 1].sin_addr, sendIp, 256);

							std::cout << "<SERVER> Message sent to client at " << sendIp << "!" << std::endl;
						}
					}
				}
				if (packet.message == 3) {
					int index = m_players[port];
					m_players[port] = 0;
					playerNum--;
					m_clients.erase(m_clients.begin() + (index - 1));
				}
			}

		}
	}
}

void Server::close() {
	// Close socket
	closesocket(in);

	// Shutdown winsock
	WSACleanup();
}
