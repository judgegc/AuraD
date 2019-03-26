#include "Logger.h"
#include "Core/Util.h"
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
namespace Log
{
void Logger::Log(const std::wstring & formatted)
{
	using namespace std::string_literals;

	Write(L"["s + Core::Timestamp() + L"] "s + formatted + newline);
}
}