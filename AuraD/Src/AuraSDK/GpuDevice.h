#pragma once
#include "Device.h"
#include "API.h"
#include "Type.h"
namespace AuraSDK
{
class GpuDevice : public Device
{
public:
	static Enumerator Enumerate;
	explicit GpuDevice(const API & api, GPULightControl hDevice);
private:
	virtual void SetMode(API::DeviceMode mode) override;
	virtual DWORD LedCount() override;
	virtual void ApplyColorArray() override;
};
}