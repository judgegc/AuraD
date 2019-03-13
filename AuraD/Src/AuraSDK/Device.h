#pragma once
#include "API.h"
#include "Type.h"
#include "Color.h"
#include "LED.h"
#include <AURALightingSDK.h>
#include <vector>
#include <memory>
namespace AuraSDK
{
class Device: public std::enable_shared_from_this<Device>
{
public:
	friend class LED;
	explicit Device(const API& api, AnyHandle hDevice);
	void SetColor(const Color& color);
	LedList AllLeds();
	virtual ~Device() = default;
private:
	virtual void SetMode(API::DeviceMode mode) = 0;
	virtual DWORD LedCount() = 0;
	virtual void ApplyColorArray() = 0;
protected:
	const API& api;
	GPULightControl hDevice;
	std::vector<Color::ComponentType> colorArray;
};
}
