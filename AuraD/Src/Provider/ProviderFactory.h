#pragma once
#include "SourceInfo.h"
#include "BatchQuery.h"

#include <memory>
namespace Provider
{
class ProviderFactory
{
public:
	std::unique_ptr<BatchQuery> CreateBatchQuery(SourceInfo::Schema type);
};
}