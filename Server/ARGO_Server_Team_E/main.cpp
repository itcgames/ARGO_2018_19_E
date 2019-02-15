// ToDO:
//		Change SOCK_STREAM to SOCK_DGRAM
//		Change send and recv to sendto and recvfrom
//		Swap array of sockets to array of ips (map)
//		No listening in server
//		No connect in client
//		Change bind
//		No accept in server

#include <iostream>
#include "Server.h"

void main()
{
	Server* server = new Server;
	server->Bind();
	server->loop();
	server->close();
	system("pause");
}