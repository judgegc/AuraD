#pragma once
#include <cstdint>
namespace ColorSchema
{
struct ColorModel
{
	virtual uint8_t Components() const = 0;
	virtual void SetComponent(uint8_t idx, double value) = 0;
	virtual ~ColorModel() = default;
};
}
