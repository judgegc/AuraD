#include "RgbAdapter.h"
namespace ColorSchema {
RgbAdapter::RgbAdapter(const Rgb & target): target(target)
{
}
RgbAdapter::operator AuraSDK::Color()
{
	return AuraSDK::Color(
		static_cast<AuraSDK::Color::ComponentType>(target.Red()),
		static_cast<AuraSDK::Color::ComponentType>(target.Green()),
		static_cast<AuraSDK::Color::ComponentType>(target.Blue()));
}
}