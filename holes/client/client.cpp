// client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	WSABUF databuf;
	char message[] = "Newdfsdff";
	DWORD sendBytes = 0;

	WSAEVENT event;
	WSAOVERLAPPED overlapped;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "something is wrong" << std::endl;
		return -1;
	}

	SOCKADDR_IN servAddr;
	SOCKET clientSocket;
	int strLen = 0;

	clientSocket = WSASocket(PF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "clientSocket is wrong" << std::endl;
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

	event = WSACreateEvent();
	memset(&overlapped, 0, sizeof(overlapped));
	overlapped.hEvent = event;

	databuf.len = strlen(message);
	databuf.buf = message;

	if (WSASend(clientSocket, &databuf, 1, &sendBytes, 0, &overlapped, nullptr) == SOCKET_ERROR)
	{
		std::cout << "WSASend is wrong" << WSAGetLastError() << std::endl;
		return -1;
	}

	puts("지금 전송 보내고 딴짓중");

	WSAWaitForMultipleEvents(1, &event, TRUE, WSA_INFINITE, FALSE);
	WSAGetOverlappedResult(clientSocket, &overlapped, &sendBytes, FALSE, NULL);

	printf("전송된 바이트 : %d", sendBytes);

	Sleep(1000000);

	WSACleanup();

	return 0;
}

