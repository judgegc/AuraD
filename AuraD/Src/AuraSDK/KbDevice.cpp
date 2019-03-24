#include "KbDevice.h"
namespace AuraSDK
{
Enumerator KbDevice::Enumerate = &API::EnumerateKbController;
KbDevice::KbDevice(const API & api, ClaymoreKeyboardLightControl hDevice) : Device(api, hDevice) {}
void KbDevice::SetMode(API::DeviceMode mode)
{
	api.SetKbMode(hDevice, mode);
}

DWORD KbDevice::LedCount()
{
	return api.GetMbLedCount(hDevice);
}

void KbDevice::ApplyColorArray()
{
	api.SetMbColor(hDevice, colorArray);
}
}