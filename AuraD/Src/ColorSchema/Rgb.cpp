#include "Rgb.h"
#include <array>
namespace ColorSchema
{
uint8_t Rgb::Red() const
{
	return red;
}
uint8_t Rgb::Green() const
{
	return green;
}
uint8_t Rgb::Blue() const
{
	return blue;
}
uint8_t Rgb::Components() const
{
	return 3;
}
void Rgb::SetComponent(uint8_t idx, double value)
{
	std::array<uint8_t*, 3> comp{ &red, &green, &blue };
	*comp[idx] = static_cast<uint8_t>(value);
}
}