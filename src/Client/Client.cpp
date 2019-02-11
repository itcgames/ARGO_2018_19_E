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
	
	int bytesReceived = recv(sock, buf, 4096, 0);
	if (bytesReceived > 0 && std::string(buf, 0, bytesReceived) != "Welcome to the Awesome Chat Server!\r\n")
	{
		// Echo response to console
		std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
		std::string newPos = std::string(buf, 0, bytesReceived);

		std::string delimiter = ",";
		size_t pos = 0;
		std::string token;

		pos = newPos.find(delimiter);
		token = newPos.substr(0, pos);
		newPos.erase(0, pos + delimiter.length());
		if (token == "Join") {
			while ((pos = newPos.find(delimiter)) != std::string::npos) {
				token = newPos.substr(0, pos);
				m_joiners.push_back(atoi(token.c_str()));
				newPos.erase(0, pos + delimiter.length());
			}
		}
		if (token == "Leave") {
			while ((pos = newPos.find(delimiter)) != std::string::npos) {
				token = newPos.substr(0, pos);
				m_leavers.push_back(atoi(token.c_str()));
				newPos.erase(0, pos + delimiter.length());
			}
		}
		if (token == "number") {
			while ((pos = newPos.find(delimiter)) != std::string::npos) {
				token = newPos.substr(0, pos);
				number = atoi(token.c_str());
				newPos.erase(0, pos + delimiter.length());
			}
		}
		
	}
}

void Client::sendMessage(std::string message) {
	ZeroMemory(buf, 4096);
	if (message.size() > 0)		// Make sure the user has typed in something
	{
		// Send the text
		int sendResult = send(sock,message.c_str(), message.size() + 1, 0);
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