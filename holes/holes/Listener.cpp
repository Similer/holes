#include "stdafx.h"
#include "Listener.h"


Listener::Listener()
{
}


Listener::~Listener()
{
}


bool Listener::Initialize()
{
	mSocket = WSASocket(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);

	mServAddr.sin_family = AF_INET;
	mServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	mServAddr.sin_port = PORT;

	bind(mSocket, (SOCKADDR*)&mServAddr, sizeof(mServAddr));
	listen(mSocket, BACK_LOG);



	return true;
}
