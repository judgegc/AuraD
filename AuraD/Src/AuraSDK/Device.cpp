#include "Device.h"
#include "Type.h"
#include <algorithm>
#include <iterator>
#include <memory>
namespace AuraSDK
{
Device::Device(const API & api, AnyHandle hDevice) :
	api(api), hDevice(hDevice), colorArray(api.GetGPULedCount(hDevice) * Color::ComponentCount) {}
void Device::SetColor(const Color & color)
{
	size_t idx = 0;
	std::generate(colorArray.begin(), colorArray.end(), [&]()
	{
		return color.Component(static_cast<Color::ComponentIdx>(idx++ % Color::ComponentCount));
	});

	SetMode(API::DeviceMode::SOFT);
	ApplyColorArray();
}
LedList Device::AllLeds()
{
	LedList leds;
	DWORD count = LedCount();
	leds.reserve(count);

	size_t locIndex = 0;
	std::generate_n(std::back_inserter(leds), count, [&]()
	{
		size_t i = locIndex;
		locIndex += Color::ComponentCount;
		return std::make_unique<LED>(shared_from_this(), colorArray.begin() + i);
	});

	return leds;
}
}