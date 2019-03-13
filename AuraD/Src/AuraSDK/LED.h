#pragma once
#include "API.h"
#include "Color.h"
#include "Type.h"
#include <AURALightingSDK.h>
#include <iterator>
#include <memory>
namespace AuraSDK
{
class LED
{
	using ColorArrayLoc = std::vector<Color::ComponentType>::iterator;
public:
	explicit LED(DevicePtr device, ColorArrayLoc loc);
	void SetColor(const Color& color);
private:
	DevicePtr device;
	ColorArrayLoc loc;
};
}
