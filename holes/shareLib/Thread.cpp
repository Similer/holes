#include "stdafx.h"
#include "Thread.h"


Thread::Thread()
{
}


Thread::~Thread()
{
}


unsigned Thread::GQCS(void* completionPort)
{
	HANDLE hCompletionPort = (HANDLE)completionPort;
	DWORD bytesTransferd = 0;
	Session* session = nullptr;
	MyOverlapped* overlapped = nullptr;
	DWORD flags;

	while (1)
	{
		GetQueuedCompletionStatus(hCompletionPort, &bytesTransferd, (LPDWORD)&session, (OVERLAPPED**)&overlapped, INFINITE);

		if (bytesTransferd == 0)
		{
			std::cout << "GetQueuedCompletionStatus is wrong" << std::endl;
			continue;
		}

		/// 여기서 에코 하고~


		// 다시 세팅
		overlapped->wsabuf.len = BUFSIZE;
		overlapped->wsabuf.buf = overlapped->buffer;

		flags = 0;

		// 리시브 다시 걸고 ~
		session->PreRecv();
	}

	return 0;
}
