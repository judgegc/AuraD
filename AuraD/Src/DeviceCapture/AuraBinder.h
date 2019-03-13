#pragma once
#include "AuraSDK/DeviceEnumerator.h"
#include "AuraSDK/LED.h"
#include "CaptureUnit.h"

#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
namespace DeviceCapture
{
class AuraBinder
{
	const AuraSDK::DeviceEnumerator& enumerator;
public:
	explicit AuraBinder(const AuraSDK::DeviceEnumerator& enumerator);
	std::vector<std::unique_ptr<AuraSDK::LED>> Bind(const CaptureUnit& unit);
private:
	struct DeviceAccessor
	{
		const CaptureUnit& target;
		const decltype(CaptureUnit::deviceIdx)& operator()() { return target.deviceIdx; };
	};
	struct LedAccessor
	{
		const CaptureUnit& target;
		const decltype(CaptureUnit::ledIdx)& operator()() { return target.ledIdx; };
	};
	template<typename A, typename T>
	static void ForEach(T&& dev, const CaptureUnit& unit, std::function<void(typename T::value_type&)> fn);
};
template<typename A, typename T>
inline void AuraBinder::ForEach(T&& dev, const CaptureUnit& unit, std::function<void(typename T::value_type&)> fn)
{
	A accessor{ unit };
	if (accessor().empty())
	{
		for (typename T::value_type& x : dev)
		{
			fn(x);
		}
	}
	else
	{
		for (auto x : accessor())
		{
			if (x < dev.size())
			{
				fn(dev[x]);
			}
		}
	}
}
}
