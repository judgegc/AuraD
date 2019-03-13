#pragma once
#include <cstdint>
#include <array>
namespace AuraSDK
{
class Color
{
public:
	using ComponentType = uint8_t;
	enum class ComponentIdx { RED, GREEN, BLUE };

	friend class API;

	explicit Color(ComponentType r, ComponentType g, ComponentType b);
	ComponentType Red() const;
	ComponentType Green() const;
	ComponentType Blue() const;
	ComponentType Component(const ComponentIdx index) const;
	static const int ComponentCount = 3;
private:
	std::array<ComponentType, ComponentCount> value;
};
}
