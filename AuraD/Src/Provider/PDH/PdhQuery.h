#pragma once
#include "Core/AutoIncrement.h"

#include <Windows.h>
#include <Pdh.h>
#include <string>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <functional>

namespace Provider::PDH
{
class PdhQuery
{
public:
	PdhQuery();
	uint64_t AddCounter(const std::wstring& uri);
	void Execute();
	uint64_t FetchValue(uint64_t counter);
private:
	void CheckErrors();
private:
	Core::AutoIncrement id;
	HQUERY query;
	PDH_STATUS status;
	std::unordered_map<uint64_t, HCOUNTER> counterMap;
};
}
