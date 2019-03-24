#include "FileLogger.h"
#include "Core/Util.h"
namespace Log {
FileLogger::FileLogger(const std::wstring & filename) : logfile(filename, std::ios::app | std::ios::binary) {}
FileLogger::~FileLogger()
{
	logfile.close();
}
void FileLogger::Write(const std::wstring & formatted)
{
	if (!logfile.is_open())
		return;

	std::string data = Core::Utf16ToUtf8(formatted);
	logfile.write(data.data(), data.size());
	logfile.flush();
}
}