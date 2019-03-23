#include "AuraBinder.h"
#include "AuraSDK/Device.h"
#include "AuraSDK/GpuDevice.h"
#include <AuraSDK/MbDevice.h>
#include <memory>
#include <algorithm>
namespace DeviceCapture
{
AuraBinder::AuraBinder(const AuraSDK::DeviceEnumerator& enumerator) : enumerator(enumerator) {}
std::vector<std::unique_ptr<AuraSDK::LED>> AuraBinder::Bind(const CaptureUnit & unit)
{
	std::vector<std::shared_ptr<AuraSDK::Device>> dev;
	switch (unit.type)
	{
	case CaptureUnit::DeviceType::GPU:
	{
		auto gpu = enumerator.GetAll<AuraSDK::GpuDevice>();
		dev.resize(gpu.size());
		std::move(gpu.begin(), gpu.end(), dev.begin());
		break;
	}
	case CaptureUnit::DeviceType::MOTHERBOARD:
	{
		auto mbr = enumerator.GetAll<AuraSDK::MbDevice>();
		dev.resize(mbr.size());
		std::move(mbr.begin(), mbr.end(), dev.begin());
		break;
	}
	case CaptureUnit::DeviceType::KEYBARD:
	case CaptureUnit::DeviceType::MOUSE:
		throw std::runtime_error("Keyboard and mouse interface not implemented yet");
	}

	std::vector<std::unique_ptr<AuraSDK::LED>> ret;
	ForEach<DeviceAccessor>(std::forward<decltype(dev)>(dev), unit, [&](std::shared_ptr<AuraSDK::Device>& d)
	{
		ForEach<LedAccessor>(d->AllLeds(), unit, [&](std::unique_ptr<AuraSDK::LED>& l)
		{
			ret.push_back(std::move(l));
		});
	});
	return ret;
}
}