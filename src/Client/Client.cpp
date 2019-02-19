#include "Client.h"

Client::Client(std::string ip, int port) : ipAddress(ip), port(port) {										// Initialize WinSock
	
}

Client::~Client() {
	closesocket(sock);
	WSACleanup();
}

void Client::receive() {
	packet = new Packet();
	m_serverSize = sizeof(hint);
	int bytesReceived = recvfrom(sock, (char*)packet, sizeof(struct Packet) + 1, 0, (sockaddr*)&hint, &m_serverSize);
	if (packet->playerNum > 0)
	{
		// Echo response to console
		std::cout << "SERVER> " << packet->message << std::endl;
		
		if (packet->message == 1) {
			number = packet->playerNum;
		}
		if (packet->message == 2) {
			m_joiners.push_back(packet->playerNum);
		}
		if (packet->message == 3) {
			m_leavers.push_back(packet->playerNum);
		}
		if (packet->message == 4) {
			m_startGame = true;
		}
		if (packet->message == 5) {
			
		}
	}
}

void Client::sendMessage(Packet packet) {
	if (sizeof(packet) + 1 > 0)		// Make sure the user has typed in something
	{
		// Send the text
		int sendResult = sendto(sock, (char*)&packet, sizeof(struct Packet) + 1, 0, (sockaddr*)&hint, sizeof(hint));
	}
}

bool Client::run() {
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
		return false;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}
	u_long iMode = 1;
	ioctlsocket(sock, FIONBIO, &iMode);
	// Fill in a hint structure

	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	Packet * p = new Packet();
	p->message = -5;

	sendto(sock, (char*)p, sizeof(struct Packet) + 1, 0, (sockaddr*)&hint, sizeof(hint));

	return true;
}