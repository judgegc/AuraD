#include "Color.h"
namespace AuraSDK
{
Color::Color(ComponentType r, ComponentType g, ComponentType b) : value{ r, g, b } {}

Color::ComponentType AuraSDK::Color::Red() const
{
	return value[static_cast<decltype(value)::size_type>(Color::ComponentIdx::RED)];
}

Color::ComponentType AuraSDK::Color::Green() const
{
	return value[static_cast<decltype(value)::size_type>(Color::ComponentIdx::GREEN)];
}

Color::ComponentType AuraSDK::Color::Blue() const
{
	return value[static_cast<decltype(value)::size_type>(Color::ComponentIdx::BLUE)];
}
Color::ComponentType Color::Component(const ComponentIdx index) const
{
	return value[static_cast<size_t>(index)];
}
}
