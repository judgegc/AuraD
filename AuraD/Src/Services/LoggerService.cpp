#include "LoggerService.h"
#include "Core/Exception.h"
namespace Services
{
Log::Logger * LoggerService::Instance()
{
	if (!instance)
		throw Core::Exception(L"Using non initialized LoggerService.");
	return instance.get();
}
std::unique_ptr<Log::Logger> LoggerService::instance;
}