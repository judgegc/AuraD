#pragma once
#include "Log/Logger.h"
#include <memory>
namespace Services
{
class LoggerService
{
public:
	template<typename T, typename ...Args>
	static inline void Initialize(Args... args)
	{
		static_assert(std::is_base_of<Log::Logger, T>::value, "T must derive from Logger.");

		instance = std::make_unique<T>(args...);
	}
	static Log::Logger* Instance();
private:
	static std::unique_ptr<Log::Logger> instance;
};
}
