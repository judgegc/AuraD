#pragma once
#include <string>
#include <fstream>

#include "Logger.h"
namespace Log
{
class FileLogger: public Logger
{
public:
	explicit FileLogger(const std::wstring& filename);
	virtual ~FileLogger();
private:
	std::ofstream logfile;
private:
	virtual void Write(const std::wstring & formatted) override;
};
}
