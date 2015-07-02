#pragma once

class Session
{
public:
	Session();
	virtual ~Session();

private:
	SOCKET mSocket;
	SOCKADDR_IN mAddrInfo;

};

