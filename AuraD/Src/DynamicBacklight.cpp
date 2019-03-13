#include "DynamicBacklight.h"
#include "Provider/PDH/PdhQuery.h"
#include "Syntax/Cursor.h"
#include "DeviceCaptureReader.h"
#include "ColorSchemaReader.h"
#include "AuraSDK/DeviceEnumerator.h"
#include "DeviceCapture/AuraBinder.h"
#include "DataSourceReader.h"

#include "Syntax/Cursor.h"
#include "Syntax/Identifier.h"
#include "Syntax/TokenNode.h"
#include "Provider/ProviderFactory.h"


#include <algorithm>
#include <atomic>
#include <thread>
#include <functional>

DynamicBacklight::DynamicBacklight(const std::vector<std::wstring>& options) : options(options)
{
}

void DynamicBacklight::Process(const std::wstring & opt)
{
	using namespace AuraSDK;
	using namespace Syntax;
	using namespace Provider;
	using namespace DeviceCapture;

	Cursor it(&opt);

	DeviceCaptureReader dr;
	auto capturedDevices = dr(it);

	ColorSchemaReader cr;
	auto colorSchema = cr(it);

	DeviceEnumerator enumerator(aura);
	AuraBinder binder(enumerator);

	std::vector<std::unique_ptr<AuraSDK::LED>> ledList;

	for (auto device : capturedDevices)
	{
		auto leds = binder.Bind(device);
		std::move(leds.begin(), leds.end(), std::back_inserter(ledList));
	}


	DataSourceReader dsr;
	auto source = dsr(it);

	BatchQuery* q = CreateBatchQuery(source.protocol);
	unitList.push_back({ std::move(ledList), std::move(colorSchema), q, q->AddRequest(source.source), {0, 100} });

	it.NextData();
	if (it.AtEnd())
		return;

	RangeReader rr;
	auto range = rr(it);
	unitList.back().range = range;
}

Provider::BatchQuery * DynamicBacklight::CreateBatchQuery(Provider::SourceInfo::Schema type)
{
	using namespace Provider;

	auto cachedQuery = std::find_if(batchProviderCache.begin(), batchProviderCache.end(), [&](const BatchCachedPair& x) { return x.type == type;  });

	if (cachedQuery != batchProviderCache.end())
		return cachedQuery->provider.get();

	ProviderFactory provider;
	batchProviderCache.push_back({ type,  provider.CreateBatchQuery(type) });

	return batchProviderCache.back().provider.get();
}

double DynamicBacklight::Normalize(int64_t min, int64_t max, int64_t value) const
{
	return static_cast<double>(value) / (max - min);
}

void DynamicBacklight::Run()
{
	using namespace std::placeholders;
	for (auto o : options)
		Process(o);

	extern std::atomic<bool> IsWorking;
	while (IsWorking)
	{
		for (BatchCachedPair& p : batchProviderCache)
		{
			p.provider->Execute();
		}

		for (Unit& u : unitList)
		{
			for (std::unique_ptr<AuraSDK::LED>& l : u.ledList)
			{
				double position = Normalize(u.range.start, u.range.stop, u.dataProvider->FetchValue(u.responseId));
				l->SetColor(u.colorSchema->Get(position));
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
		}
	}
}

DynamicBacklight::~DynamicBacklight()
{
	for (Unit& u : unitList)
	{
		for (std::unique_ptr<AuraSDK::LED>& l : u.ledList)
		{
			l->SetColor(AuraSDK::Color(0, 0, 0));
		}
	}
}
