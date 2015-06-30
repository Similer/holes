#pragma once

class Thread;

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	bool Initialize();

private:
	WSADATA mWsaData;
	HANDLE	mCompletionPort;

	std::vector<Thread*> mThread;


};

