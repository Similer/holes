#pragma once
class Thread
{
public:
	Thread();
	virtual ~Thread();

	static unsigned WINAPI GQCS(void* completionPort);
};

