#pragma once
#include "Device.h"
#include "API.h"
#include "Type.h"
namespace AuraSDK
{
class MbDevice: public Device
{
public:
	static Enumerator Enumerate;
	explicit MbDevice(const API& api, MbLightControl hDevice);
private:
	virtual void SetMode(API::DeviceMode mode) override;
	virtual DWORD LedCount() override;
	virtual void ApplyColorArray() override;
};

}