#include "GpuDevice.h"
namespace AuraSDK
{
Enumerator GpuDevice::Enumerate = &API::EnumerateGPU;
GpuDevice::GpuDevice(const API & api, GPULightControl hDevice) : Device(api, hDevice) {}
void GpuDevice::SetMode(API::DeviceMode mode)
{
	api.SetGPUMode(hDevice, mode);
}

DWORD GpuDevice::LedCount()
{
	return api.GetGPULedCount(hDevice);
}

void GpuDevice::ApplyColorArray()
{
	api.SetGPUColor(hDevice, colorArray);
}
}
