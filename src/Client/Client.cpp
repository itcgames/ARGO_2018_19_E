#include "Client.h"

Client::Client(std::string ip, int port) : ipAddress(ip), port(port) {										// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		std::cerr << "Can't start Winsock, Err #" << wsResult << std::endl;
		return;
	}

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		std::cerr << "Can't create socket, Err #" << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}
	
	// Fill in a hint structure
	
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
}

Client::~Client() {
	closesocket(sock);
	WSACleanup();
}

void Client::receive() {
	// Wait for response
	ZeroMemory(buf, 4096);
	
	Packet * packet = new Packet();
	int bytesReceived = recv(sock, (char*)packet, sizeof(struct Packet) + 1, 0);
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
		
	}
}

void Client::sendMessage(Packet packet) {
	ZeroMemory(buf, 4096);
	if (sizeof(packet) + 1 > 0)		// Make sure the user has typed in something
	{
		// Send the text
		int sendResult = send(sock, (char*)&packet, sizeof(struct Packet) + 1, 0);
	}
}

bool Client::run() {
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect to server, Err #" << WSAGetLastError() << std::endl;
		closesocket(sock);
		WSACleanup();
		return false;
	}
	u_long iMode = 1;
	ioctlsocket(sock, FIONBIO, &iMode);
	return true;
}