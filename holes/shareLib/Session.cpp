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
#pragma todo("overlapped �̰� ť�� ���� ��������")

	MyOverlapped* overlapped = new MyOverlapped;
	memset(&overlapped->overlapped, 0, sizeof(overlapped->overlapped));
	overlapped->wsabuf.len = BUFSIZE;
	overlapped->wsabuf.buf = overlapped->buffer;
	DWORD Flags = 0;

	WSARecv(mSocket, &overlapped->wsabuf, 1, nullptr, &Flags, &(overlapped->overlapped), nullptr);
}

