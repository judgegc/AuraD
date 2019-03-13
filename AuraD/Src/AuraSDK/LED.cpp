#include "LED.h"
#include "Device.h"
#include <algorithm>
#include <vector>
namespace AuraSDK
{
LED::LED(DevicePtr device, ColorArrayLoc loc) :
	device(device), loc(loc) {}
void LED::SetColor(const Color & color)
{
	std::vector<Color::ComponentType> newColor{ color.Red(), color.Green(), color.Blue() };
	std::copy(newColor.cbegin(), newColor.cend(), loc);
	device->ApplyColorArray();
}
}