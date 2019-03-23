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

	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	Write(L"["s + Core::Timestamp() + L"] "s + formatted + newline);
}
}