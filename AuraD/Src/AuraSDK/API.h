#pragma once
#include "Core/Exception.h"
#include "Core/GetLastErrorAsString.h"

#include <Windows.h>
#include <iostream>
#include <exception>
#include <vector>
#include <AURALightingSDK.h>
namespace AuraSDK
{
class API
{
public:
	enum class DeviceMode { DEFAULT, SOFT };

	explicit API();
	explicit API(const std::wstring& libPath);
	virtual ~API();
	void Initialize(const std::wstring& libPath = L"AURA_SDK.dll");
	void Terminate();
	DWORD EnumerateGPU(GPULightControl handles[], DWORD size) const;
	DWORD SetGPUMode(GPULightControl handle, DeviceMode mode) const;
	DWORD SetGPUColor(GPULightControl handle, const std::vector<BYTE>& color) const;
	DWORD GetGPULedCount(GPULightControl handle) const;

	DWORD EnumerateMb(MbLightControl handles[], DWORD size) const;
	DWORD SetMbMode(MbLightControl handle, DeviceMode mode) const;
	DWORD SetMbColor(MbLightControl handle, const std::vector<BYTE>& color) const;
	DWORD GetMbColor(MbLightControl handle, std::vector<BYTE>& color) const;
	DWORD GetMbLedCount(MbLightControl handle) const;

	DWORD EnumerateKbController(ClaymoreKeyboardLightControl handles[], DWORD) const;
	DWORD SetKbMode(ClaymoreKeyboardLightControl handle, DeviceMode mode) const;
	DWORD SetKbColor(ClaymoreKeyboardLightControl handle, const std::vector<BYTE>& color) const;
	DWORD GetKbLedCount(ClaymoreKeyboardLightControl handle) const;
private:
	HMODULE hLib;
	EnumerateGPUFunc EnumerateGPUPtr;
	SetGPUModeFunc SetGPUModePtr;
	SetGPUColorFunc SetGPUColorPtr;
	GetGPULedCountFunc GetGPULedCountPtr;

	EnumerateMbControllerFunc EnumerateMbControllerPtr;
	SetMbModeFunc SetMbModePtr;
	SetMbColorFunc SetMbColorPtr;
	GetMbColorFunc GetMbColorPtr;
	GetMbLedCountFunc GetMbLedCountPtr;

	CreateClaymoreKeyboardFunc EnumerateKbControllerPtr;
	SetClaymoreKeyboardModeFunc SetKbModePtr;
	SetClaymoreKeyboardColorFunc SetKbColorPtr;
	GetClaymoreKeyboardLedCountFunc GetKbLedCountPtr;
};

template<typename R>
auto GetAPIEntry(HMODULE hModule, LPCSTR funcName)
{
	R entryPtr = reinterpret_cast<R>(::GetProcAddress(hModule, funcName));
	if (entryPtr == nullptr)
		throw Core::Exception(Core::GetLastErrorAsString());
	return entryPtr;
}

}