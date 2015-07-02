#include "stdafx.h"
#include "Listener.h"
#include "Session.h"

Listener::Listener()
{
}


Listener::~Listener()
{
}


bool Listener::Initialize()
{
	if (Session::Initialize() == false)
		return false;

	mSocket = WSASocket(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if (mSocket == INVALID_SOCKET)
	{
		GLogger->Log(_T("Session::Initialize Error : %d"), WSAGetLastError());
		return false;
	}

	return true;
}

bool Listener::Bind(int port)
{
	memset(&mAddrInfo, 0, sizeof(mAddrInfo));
	mAddrInfo.sin_family = AF_INET;
	mAddrInfo.sin_addr.s_addr = htonl(INADDR_ANY);
	mAddrInfo.sin_port = htons(port);

	if (bind(mSocket, (SOCKADDR*)&mAddrInfo, sizeof(mAddrInfo)) == SOCKET_ERROR)
	{
		GLogger->Log(_T("Listener::Bind bind Error : %d"), WSAGetLastError());
		return false;
	}

	return true;
}

bool Listener::Listen(int backlog)
{
	if (listen(mSocket, backlog) == SOCKET_ERROR)
	{
		GLogger->Log(_T("Listener::Listen listen Error : %d"), WSAGetLastError());
		return false;
	}

	return true;
}

bool Listener::Accept(Session* newSession)
{
	int szAddr = sizeof(*newSession->GetAddrInfo());
	
	SOCKET acceptedSocket = accept(mSocket, (SOCKADDR*)(newSession->GetAddrInfo()), &szAddr);
	if (acceptedSocket == INVALID_SOCKET)
	{
		GLogger->Log(_T("Listener::Accept accept Error : %d"), WSAGetLastError());
		return false;
	}

	newSession->SetSocket(acceptedSocket);

	return true;
}