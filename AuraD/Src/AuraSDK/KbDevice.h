#pragma once
#include "Device.h"
#include "API.h"
#include "Type.h"
namespace AuraSDK
{
class KbDevice : public Device
{
public:
	static Enumerator Enumerate;
	explicit KbDevice(const API& api, ClaymoreKeyboardLightControl hDevice);
private:
	virtual void SetMode(API::DeviceMode mode) override;
	virtual DWORD LedCount() override;
	virtual void ApplyColorArray() override;
};

}