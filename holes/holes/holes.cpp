// holes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../protobuf/gen/PDL.pb.h"


#define BUFSIZE 1024

unsigned int CALLBACK CompletionThread(void* CompletioPortIO);

struct MySocket
{
	SOCKET socket;
	SOCKADDR_IN addr;
};

struct MyOverlapped
{
	WSAOVERLAPPED overlapped;
	char buffer[BUFSIZE];
	WSABUF wsabuf;
};


int _tmain(int argc, _TCHAR* argv[])
{

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout << "something is wrong" << std::endl;
		return -1;
	}

	HANDLE completionPort;
	SYSTEM_INFO sysinfo;
	
	MySocket listener;

	completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);


	/// Thread를 CPU 개수만큼 생성
	GetSystemInfo(&sysinfo);
	for (unsigned int i = 0; i < sysinfo.dwNumberOfProcessors; ++i)
	{
		_beginthreadex(nullptr, 0, CompletionThread, completionPort, 0, nullptr);
	}
	
	listener.socket = WSASocket(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);
	memset(&listener.addr, 0, sizeof(listener.addr));
	listener.addr.sin_family = AF_INET;
	listener.addr.sin_addr.s_addr = htonl(INADDR_ANY);
	listener.addr.sin_port = htons(7004);

	if (bind(listener.socket, (SOCKADDR*)&listener.addr, sizeof(listener.addr)) == SOCKET_ERROR)
	{
		std::cout << "bind is wrong" << std::endl;
		return -1;
	}

	if (listen(listener.socket, 5) == SOCKET_ERROR)
	{
		std::cout << "listen is wrong" << std::endl;
		return -1;
	}

	while (1)
	{
		MySocket* client = new MySocket;
		int addrLen = sizeof(client->addr);
		client->socket = accept(listener.socket, (SOCKADDR*)&client->addr, &addrLen);

		CreateIoCompletionPort((HANDLE)client->socket, completionPort, (ULONG_PTR)client, 0);
		MyOverlapped* overlapped = new MyOverlapped;
		memset(&overlapped->overlapped, 0, sizeof(overlapped->overlapped));
		overlapped->wsabuf.len = BUFSIZE;
		overlapped->wsabuf.buf = overlapped->buffer;
		DWORD Flags = 0;
		
		WSARecv(client->socket, &overlapped->wsabuf, 1, nullptr, &Flags, &(overlapped->overlapped), nullptr);
	}

	WSACleanup();


	return 0;
}

unsigned int CALLBACK CompletionThread(void* CompletioPortIO)
{
	HANDLE hCompletionPort = (HANDLE)CompletioPortIO;
	DWORD bytesTransferd = 0;
	MySocket* client = nullptr;
	MyOverlapped* overlapped = nullptr;
	DWORD flags;

	while (1)
	{
		GetQueuedCompletionStatus(hCompletionPort, &bytesTransferd, (LPDWORD)&client, (OVERLAPPED**)&overlapped, INFINITE);

		if (bytesTransferd == 0)
		{
			std::cout << "GetQueuedCompletionStatus is wrong" << std::endl;
			continue;
		}

		/// 여기서 에코 하고~


		// 다시 세팅
		overlapped->wsabuf.len = BUFSIZE;
		overlapped->wsabuf.buf = overlapped->buffer;

		flags = 0;

		// 리시브 다시 걸고 ~
		WSARecv(client->socket, &overlapped->wsabuf, 1, nullptr, &flags, &(overlapped->overlapped), nullptr);
	}
}