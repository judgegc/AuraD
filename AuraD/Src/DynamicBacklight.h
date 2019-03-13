#pragma once
#include "Subprogram.h"
#include "Provider/SourceInfo.h"
#include "Provider/BatchQuery.h"
#include "AuraSDK/LED.h"
#include "AuraSDK/API.h"
#include "ColorSchema/Gradient.h"
#include "RangeReader.h"

#include <vector>
#include <string>
#include <memory>

class DynamicBacklight: public Subprogram
{
public:
	explicit DynamicBacklight(const std::vector<std::wstring>& options);
	virtual void Run() override;
	virtual ~DynamicBacklight();
private:
	struct BatchCachedPair
	{
		Provider::SourceInfo::Schema type;
		std::unique_ptr<Provider::BatchQuery> provider;
	};
	struct Unit
	{
		std::vector<std::unique_ptr<AuraSDK::LED>> ledList;
		std::unique_ptr<ColorSchema::Gradient> colorSchema;
		Provider::BatchQuery* dataProvider;
		uint64_t responseId;
		RangeReader::Range range;
	};
private:
	void Process(const std::wstring& opt);
	Provider::BatchQuery* CreateBatchQuery(Provider::SourceInfo::Schema type);
	double Normalize(int64_t min, int64_t max, int64_t value) const;
private:
	AuraSDK::API aura;
	std::vector<std::wstring> options;
	std::vector<BatchCachedPair> batchProviderCache;
	std::vector<Unit> unitList;
};
