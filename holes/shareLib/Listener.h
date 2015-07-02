#pragma once

#include "Session.h"

class Listener
	: public Session
{
public:
	Listener();
	~Listener();

	virtual bool Initialize();

	bool Bind(int port);
	bool Listen(int backlog);
	bool Accept(Session* newSession);

private:

};

