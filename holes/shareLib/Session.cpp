#include "stdafx.h"
#include "Session.h"


Session::Session()
{
}


Session::~Session()
{
}

bool Session::Initialize()
{
	return true;
}

void Session::PreRecv()
{
#pragma todo("overlapped 이거 큐로 만들어서 관리하자")

	MyOverlapped* overlapped = new MyOverlapped;
	memset(&overlapped->overlapped, 0, sizeof(overlapped->overlapped));
	overlapped->wsabuf.len = BUFSIZE;
	overlapped->wsabuf.buf = overlapped->buffer;
	DWORD Flags = 0;

	WSARecv(mSocket, &overlapped->wsabuf, 1, nullptr, &Flags, &(overlapped->overlapped), nullptr);
}

