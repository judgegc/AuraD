#include "PdhAdapter.h"
namespace Provider::PDH
{
uint64_t PdhAdapter::AddRequest(const std::wstring & source)
{
	return q.AddCounter(std::wstring(L"\\") + source);
}
void PdhAdapter::Execute()
{
	q.Execute();
}
uint64_t PdhAdapter::FetchValue(uint64_t id)
{
	return q.FetchValue(id);
}
}