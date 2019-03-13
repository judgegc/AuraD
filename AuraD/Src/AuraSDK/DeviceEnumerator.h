#pragma once
#pragma warning(disable: 4200)
#include "API.h"
#include "Type.h"
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <iterator>
namespace AuraSDK
{
class DeviceEnumerator
{
public:
	explicit DeviceEnumerator(const API& api);
	template<typename T> std::vector<std::shared_ptr<T>> GetAll() const;
private:
	const API& api;
};
template<typename T>
inline std::vector<std::shared_ptr<T>> DeviceEnumerator::GetAll() const
{
	static_assert(std::is_base_of<Device, T>::value, "T must derive from Device");

	using namespace std::placeholders;
	auto Enumerate = std::bind(T::Enumerate, &api, _1, _2);
	DWORD count = Enumerate(nullptr, 0);
	std::vector<AnyHandle> rawDeviceList(count);
	Enumerate(rawDeviceList.data(), count);
	std::vector<std::shared_ptr<T>> deviceList;
	deviceList.reserve(count);

	std::transform(rawDeviceList.cbegin(),
		rawDeviceList.cend(),
		std::back_inserter(deviceList),
		[&](const AnyHandle& hDevice)
	{
		return std::make_shared<T>(api, hDevice);
	});

	return deviceList;
}
}