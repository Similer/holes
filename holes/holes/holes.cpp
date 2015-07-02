// holes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../protobuf/gen/PDL.pb.h"

struct MySocket
{
	SOCKET socket;
	SOCKADDR_IN addr;
};

int _tmain(int argc, _TCHAR* argv[])
{
	IocpCore* iocp = new IocpCore;

	if (iocp->Initialize() == false)
		return -1;
	
	Listener* listener = new Listener;
	
	if (listener->Initialize() == false)
		return -1;
	if (listener->Bind(7004) == false)
		return -1;
	if (listener->Listen(5) == false)
		return -1;

	while (1)
	{
		Session* newSession = new Session;

		if (listener->Accept(newSession) == false)
			break;

		iocp->RegistCompletionPort((HANDLE)newSession->GetSocket(), (ULONG_PTR)newSession);
		
		newSession->PreRecv();
	}

	WSACleanup();


	return 0;
}

//unsigned int CALLBACK CompletionThread(void* CompletioPortIO)
//{
//	HANDLE hCompletionPort = (HANDLE)CompletioPortIO;
//	DWORD bytesTransferd = 0;
//	MySocket* client = nullptr;
//	MyOverlapped* overlapped = nullptr;
//	DWORD flags;
//
//	while (1)
//	{
//		GetQueuedCompletionStatus(hCompletionPort, &bytesTransferd, (LPDWORD)&client, (OVERLAPPED**)&overlapped, INFINITE);
//
//		if (bytesTransferd == 0)
//		{
//			std::cout << "GetQueuedCompletionStatus is wrong" << std::endl;
//			continue;
//		}
//
//		/// 여기서 에코 하고~
//
//
//		// 다시 세팅
//		overlapped->wsabuf.len = BUFSIZE;
//		overlapped->wsabuf.buf = overlapped->buffer;
//
//		flags = 0;
//
//		// 리시브 다시 걸고 ~
//		WSARecv(client->socket, &overlapped->wsabuf, 1, nullptr, &flags, &(overlapped->overlapped), nullptr);
//	}
//}