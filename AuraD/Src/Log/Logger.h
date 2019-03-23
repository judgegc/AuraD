#pragma once
#include <string>
namespace Log {
class Logger
{
	virtual void Write(const std::wstring& formatted) = 0;
public:
	void Log(const std::wstring& msg);
	virtual ~Logger() = default;
protected:
	std::wstring newline = L"\r\n";
};
}