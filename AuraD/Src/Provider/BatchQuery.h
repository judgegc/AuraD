#pragma once
#include <string>
namespace Provider
{
struct BatchQuery
{
	virtual uint64_t AddRequest(const std::wstring& source) = 0;
	virtual void Execute() = 0;
	virtual uint64_t FetchValue(uint64_t id) = 0;
	virtual ~BatchQuery() = default;
};
}
