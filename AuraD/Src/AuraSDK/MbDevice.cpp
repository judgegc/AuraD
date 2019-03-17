#include "MbDevice.h"
namespace AuraSDK
{
Enumerator MbDevice::Enumerate = &API::EnumerateMb;
MbDevice::MbDevice(const API & api, GPULightControl hDevice) : Device(api, hDevice) {}
void MbDevice::SetMode(API::DeviceMode mode)
{
	api.SetMbMode(hDevice, mode);
}

DWORD MbDevice::LedCount()
{
	return api.GetMbLedCount(hDevice);
}

void MbDevice::ApplyColorArray()
{
	api.SetMbColor(hDevice, colorArray);
}
}