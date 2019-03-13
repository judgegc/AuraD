#include "MbDevice.h"
namespace AuraSDK
{
Enumerator MbDevice::Enumerate = &API::EnumerateMb;
MbDevice::MbDevice(const API & api, GPULightControl hDevice) : Device(api, hDevice) {}
void MbDevice::SetMode(API::DeviceMode mode)
{
	api.SetGPUMode(hDevice, mode);
}

DWORD MbDevice::LedCount()
{
	return api.GetGPULedCount(hDevice);
}

void MbDevice::ApplyColorArray()
{
	api.SetGPUColor(hDevice, colorArray);
}
}