// holes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../protobuf/gen/PDL.pb.h"

int _tmain(int argc, _TCHAR* argv[])
{
	/*IocpCore* iocp = new IocpCore;

	iocp->Initialize();

	PDL::Person pf;


	pf.set_name("gg");
	pf.set_email("Yee");
	pf.set_id(1);*/


	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "something is wrong" << std::endl;
		return -1;
	}

	SOCKADDR_IN servAddr, clientAddr;
	SOCKET listenSocket, clientSocket;

	listenSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		std::cout << "listenSocket is wrong" << std::endl;
		return -1;
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(7004);

	if (bind(listenSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cout << "bind is wrong" << std::endl;
		return -1;
	}

	if (listen(listenSocket, 5) == SOCKET_ERROR)
	{
		std::cout << "listen is wrong" << std::endl;
		return -1;
	}

	int szClientAddr = sizeof(clientAddr);
	clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &szClientAddr);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "accept is wrong" << std::endl;
		return -1;
	}
	
	char* message = "Hello world";

	char message2[] = "Hello World";

	send(clientSocket, message2, sizeof(message2), 0);

	Sleep(1000);

	WSACleanup();


	return 0;
}

