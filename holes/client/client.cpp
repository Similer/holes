// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "something is wrong" << std::endl;
		return -1;
	}

	char message[30] = { 0, };

	SOCKADDR_IN servAddr;
	SOCKET clientSocket;
	int strLen = 0;

	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		
		std::cout << "clientSocket is wrong" <<  std::endl;
		return -1;
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(7004);

	if (connect(clientSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cout << "connect is wrong" << WSAGetLastError() << std::endl;
		return -1;
	}



	strLen = recv(clientSocket, message, sizeof(message) - 1, 0);
	if (strLen == -1)
		std::cout << "recv is wrong" << std::endl;

	message[strLen] = 0;

	std::cout << message << std::endl;


	WSACleanup();

	return 0;
}

