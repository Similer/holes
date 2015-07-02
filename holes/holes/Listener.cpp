#include "stdafx.h"
#include "Listener.h"


Listener::Listener()
{
}


Listener::~Listener()
{
}


void Listener::Bind(int port)
{
	mSocket = WSASocket(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);

	mServAddr.sin_family = AF_INET;
	mServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	mServAddr.sin_port = port;

	bind(mSocket, (SOCKADDR*)&mServAddr, sizeof(mServAddr));

	listen(mSocket, BACK_LOG);



	return true;
}

void Listener::Listen()
{

}