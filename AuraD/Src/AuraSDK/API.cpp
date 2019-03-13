#include "API.h"

namespace AuraSDK {
API::API()
{
	Initialize();
}
API::API(const std::wstring& libPath)
{
	Initialize(libPath);
}
API::~API()
{
	Terminate();
}
void API::Initialize(const std::wstring& libPath)
{
	hLib = ::LoadLibrary(libPath.c_str());
	if (hLib == nullptr)
		throw Core::Exception(Core::GetLastErrorAsString());

	EnumerateGPUPtr = GetAPIEntry<EnumerateGPUFunc>(hLib, "EnumerateGPU");
	SetGPUModePtr = GetAPIEntry<SetGPUModeFunc>(hLib, "SetGPUMode");
	SetGPUColorPtr = GetAPIEntry<SetGPUColorFunc>(hLib, "SetGPUColor");
	GetGPULedCountPtr = GetAPIEntry<GetGPULedCountFunc>(hLib, "GetGPULedCount");

	EnumerateMbControllerPtr = GetAPIEntry<EnumerateMbControllerFunc>(hLib, "EnumerateMbController");
	SetMbModePtr = GetAPIEntry<SetMbModeFunc>(hLib, "SetMbMode");
	SetMbColorPtr = GetAPIEntry<SetMbColorFunc>(hLib, "SetMbColor");
	GetMbColorPtr = GetAPIEntry<GetMbColorFunc>(hLib, "GetMbColor");
	GetMbLedCountPtr = GetAPIEntry<GetMbLedCountFunc>(hLib, "GetMbLedCount");
}
void API::Terminate()
{
	::FreeLibrary(hLib);
	hLib = nullptr;
}
DWORD API::EnumerateGPU(GPULightControl handles[], DWORD size) const
{
	return EnumerateGPUPtr(handles, size);
}
DWORD API::SetGPUMode(GPULightControl handle, DeviceMode mode) const
{
	return SetGPUModePtr(handle, static_cast<int>(mode));
}
/*
color - | R | G | B | R | G | B |
*/
DWORD API::SetGPUColor(GPULightControl handle, const std::vector<BYTE>& color) const
{
	return SetGPUColorPtr(handle,
		const_cast<BYTE*>(color.data()),
		color.size() * sizeof(std::remove_reference<decltype(color)>::type::value_type));
}
DWORD API::GetGPULedCount(GPULightControl handle) const
{
	return GetGPULedCountPtr(handle);
}
DWORD API::EnumerateMb(MbLightControl handles[], DWORD size) const
{
	return EnumerateMbControllerPtr(handles, size);
}
DWORD API::SetMbMode(MbLightControl handle, DeviceMode mode) const
{
	return SetMbModePtr(handle, static_cast<int>(mode));
}
DWORD API::SetMbColor(MbLightControl handle, const std::vector<BYTE>& color) const
{
	return SetMbColorPtr(handle,
		const_cast<BYTE*>(color.data()),
		color.size() * sizeof(std::remove_reference<decltype(color)>::type::value_type));
}
DWORD API::GetMbColor(MbLightControl handle, std::vector<BYTE>& color) const
{
	return GetMbColorPtr(handle,
		color.data(),
		color.size() * sizeof(std::remove_reference<decltype(color)>::type::value_type));
}
DWORD API::GetMbLedCount(MbLightControl handle) const
{
	return GetMbLedCountPtr(handle);
}
}