#pragma once
class Thread
{
public:
	Thread();
	virtual ~Thread();

	static unsigned CALLBACK GQCS(void* completionPort);
};

