#include "ProviderFactory.h"
#include "PDH/PdhAdapter.h"
#include "Core/Exception.h"
namespace Provider
{
std::unique_ptr<BatchQuery> ProviderFactory::CreateBatchQuery(SourceInfo::Schema type)
{
	switch (type)
	{
	case SourceInfo::Schema::PDH:
		return std::make_unique<PDH::PdhAdapter>();
	default:
		throw Core::Exception(L"Unknown batch query type");
	}
}
}