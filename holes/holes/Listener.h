#pragma once

#include "Session.h"

#define PORT		7004
#define BACK_LOG	10

class Listener : public Session
{
public:
	Listener();
	~Listener();

	void Bind(int port);
	void Listen();

private:
};

