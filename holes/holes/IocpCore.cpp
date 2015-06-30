#include "stdafx.h"
#include "IocpCore.h"


IocpCore::IocpCore()
{
}


IocpCore::~IocpCore()
{
}


bool IocpCore::Initialize()
{
	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != 0)
	{
		GLogger->Log(_T("Error WSAStartUp"));
		return false;
	}

	/// Completion Port 생성
	mCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);


	/// Thread를 CPU 개수만큼 생성
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);


	for (unsigned int i = 0; i < systemInfo.dwNumberOfProcessors; ++i)
	{
		_beginthreadex(nullptr, 0, &Thread::GQCS, mCompletionPort, 0, nullptr);
	}



	

	return true;
}
