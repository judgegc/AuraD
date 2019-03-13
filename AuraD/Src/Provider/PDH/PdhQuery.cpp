#include "PdhQuery.h"
#include "Core/Exception.h"
#include "Core/GetLastErrorAsString.h"

#include <iostream>
namespace Provider::PDH
{
PdhQuery::PdhQuery() :
	query(nullptr),
	status(ERROR_SUCCESS)
{
	status = PdhOpenQuery(NULL, NULL, &query);
	CheckErrors();
}
uint64_t PdhQuery::AddCounter(const std::wstring & uri)
{
	HCOUNTER counter;
	status = PdhAddCounter(query, uri.c_str(), 0, &counter);
	CheckErrors();

	uint64_t counterId = id.Gen();
	counterMap[counterId] = counter;
	return counterId;
}

void PdhQuery::Execute()
{
	PdhCollectQueryData(query);
}

uint64_t PdhQuery::FetchValue(uint64_t counter)
{
	DWORD counterType;
	PDH_FMT_COUNTERVALUE value;
	PdhGetFormattedCounterValue(counterMap[counter], PDH_FMT_LARGE, &counterType, &value);
	return value.largeValue;
}

void PdhQuery::CheckErrors()
{
	using namespace Core;
	if (status != ERROR_SUCCESS)
		throw Exception(GetLastErrorAsString(L"pdh.dll"));
}
}