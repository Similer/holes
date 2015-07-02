#pragma once

#define _QUOTE(X) #X
#define QUOTE(X) _QUOTE(X)

#define todo(MSG) message(__FILE__ "(" QUOTE(__LINE__) ") : todo => " MSG)


#define BUFSIZE 1024

struct MyOverlapped
{
	WSAOVERLAPPED overlapped;
	char buffer[BUFSIZE];
	WSABUF wsabuf;
};


class miscUtils
{
public:
	miscUtils();
	~miscUtils();
};

