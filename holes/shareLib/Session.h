#pragma once
class Session
{
public:
	Session();
	~Session();

	virtual bool Initialize();

	void SetSocket(SOCKET socket) { mSocket = socket; }
	SOCKET GetSocket() { return mSocket; }

	SOCKADDR_IN* GetAddrInfo() { return &mAddrInfo; }

	void PreRecv();

protected:
	SOCKET		mSocket;
	SOCKADDR_IN mAddrInfo;
};

