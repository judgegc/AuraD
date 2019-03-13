#pragma once
#include <vector>
namespace DeviceCapture {
struct CaptureUnit
{
	//Update DeviceCaptureReader::NewUnit types, if change
	enum class DeviceType { ALL, GPU, MOTHERBOARD, KEYBARD, MOUSE };
	enum class Capture { ENUM, RANGE };
	DeviceType type;
	Capture deviceCap;
	Capture ledCap;
	std::vector<int> deviceIdx;
	std::vector<int> ledIdx;
};
}