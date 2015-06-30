#pragma once
class Logger
{
public:
	Logger();
	~Logger();

	void Log(const TCHAR* str);
};

extern Logger* GLogger;

