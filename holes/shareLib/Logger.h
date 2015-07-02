#pragma once
class Logger
{
public:
	Logger();
	~Logger();

	template<typename... Args>
	void Log(const TCHAR* format, Args... args)
	{
		_tprintf(format, args...);
	}
};

extern Logger* GLogger;

