#pragma once
#include "PdhQuery.h"
#include "Provider/BatchQuery.h"
namespace Provider::PDH
{
class PdhAdapter: public BatchQuery
{
public:
	virtual uint64_t AddRequest(const std::wstring& source) override;
	virtual void Execute() override;
	virtual uint64_t FetchValue(uint64_t id) override;
	virtual ~PdhAdapter() = default;
private:
	PdhQuery q;
};
}
