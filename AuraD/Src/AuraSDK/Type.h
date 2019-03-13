#pragma once
#include <cstdint>
#include <memory>
#include <vector>
namespace AuraSDK
{
class Device;
class LED;

using AnyHandle = void*;
using Enumerator = DWORD(API::*)(AnyHandle[], DWORD) const;
using DevicePtr = std::shared_ptr<Device>;
using LedPtr = std::unique_ptr<LED>;
using DeviceList = std::vector<DevicePtr>;
using LedList = std::vector<LedPtr>;
}
