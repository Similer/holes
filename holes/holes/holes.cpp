// holes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../protobuf/gen/PDL.pb.h"

int _tmain(int argc, _TCHAR* argv[])
{
	PDL::Person pf;

	pf.set_name("gg");
	pf.set_email("Yee");
	pf.set_id(1);

	return 0;
}

