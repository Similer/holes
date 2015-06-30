#pragma once

#define PORT		7004
#define BACK_LOG	10

class Listener
{
public:
	Listener();
	~Listener();
	bool Initialize();

private:
	SOCKET		mSocket;
	SOCKADDR_IN mServAddr;
};

