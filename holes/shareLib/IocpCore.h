#pragma once

#include "CommonHeader.h"

class Thread;

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	bool Initialize();
	void RegistCompletionPort(HANDLE handle, ULONG_PTR completioKey);

private:
	WSADATA mWsaData;
	HANDLE	mCompletionPort;

	std::vector<Thread*> mThread;


};

