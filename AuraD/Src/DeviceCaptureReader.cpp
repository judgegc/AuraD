#include "DeviceCaptureReader.h"
#include "Core/Exception.h"
#include "ParsingError.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <array>
#include <algorithm>
#include <exception>

bool DeviceCaptureReader::ProcessNode(Syntax::TokenNode * node)
{
	node->t->Process(cursor);
	return node->t->Success();
}

void DeviceCaptureReader::NewUnit()
{
	std::array<std::wstring, 5> types{ L"never gonna give you up", L"gpu", L"mbr", L"kbr", L"mouse" };
	auto found = std::find(types.begin(), types.end(), device.Get<Syntax::Identifier>()->Value());
	if (found == types.end())
		throw Core::Exception(L"Unknown device type.");
	result.unit.push_back({ static_cast<DeviceCapture::CaptureUnit::DeviceType>(found - types.begin()) });
}

void DeviceCaptureReader::NewAllUnit()
{
	result.unit.push_back({ DeviceCapture::CaptureUnit::DeviceType::ALL });
}

void DeviceCaptureReader::DeviceCapturedValue()
{
	result.unit.back().deviceIdx.push_back(static_cast<int>(deviceCaptureValue.Get<Syntax::Number>()->Value()));
}

void DeviceCaptureReader::DevicecaptureEndValue()
{
	result.unit.back().deviceIdx.push_back(static_cast<int>(deviceCaptureRangeEndValue.Get<Syntax::Number>()->Value()));
}

void DeviceCaptureReader::LedCapturedValue()
{
	result.unit.back().ledIdx.push_back(static_cast<int>(ledCaptureValue.Get<Syntax::Number>()->Value()));
}

void DeviceCaptureReader::LedCaptureEndValue()
{
	result.unit.back().ledIdx.push_back(static_cast<int>(ledCaptureRangeEndValue.Get<Syntax::Number>()->Value()));
}

void DeviceCaptureReader::DeviceRangeMode()
{
	result.unit.back().deviceCap = DeviceCapture::CaptureUnit::Capture::RANGE;
}

void DeviceCaptureReader::LedRangeMode()
{
	result.unit.back().ledCap = DeviceCapture::CaptureUnit::Capture::RANGE;
}

DeviceCaptureReader::DeviceCaptureReader() :
	root(nullptr),
	allDevice(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Keyword>(L"*"), std::bind(&DeviceCaptureReader::NewAllUnit, this))),
	device(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Identifier>(), std::bind(&DeviceCaptureReader::NewUnit, this))),
	deviceEnumOpen(std::make_unique<Syntax::Keyword>(L"[")),
	deviceCaptureOpen(std::make_unique<Syntax::Keyword>(L"[")),
	deviceCaptureValue(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Number>(), std::bind(&DeviceCaptureReader::DeviceCapturedValue, this))),
	deviceCaptureValueEnumSeparator(std::make_unique<Syntax::Keyword>(L",")),
	deviceCaptureValueRangeSeparator(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Keyword>(L":"), std::bind(&DeviceCaptureReader::DeviceRangeMode, this))),
	deviceCaptureRangeEndValue(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Number>(), std::bind(&DeviceCaptureReader::DevicecaptureEndValue, this))),
	deviceCaptureClose(std::make_unique<Syntax::Keyword>(L"]")),
	deviceSeparator(std::make_unique<Syntax::Keyword>(L",")),
	ledCaptureOpen(std::make_unique<Syntax::Keyword>(L"[")),
	ledCaptureValue(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Number>(), std::bind(&DeviceCaptureReader::LedCapturedValue, this))),
	ledCaptureValueEnumSeparator(std::make_unique<Syntax::Keyword>(L",")),
	ledCaptureValueRangeSeparator(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Keyword>(L":"), std::bind(&DeviceCaptureReader::LedRangeMode, this))),
	ledCaptureRangeEndValue(std::make_unique<Syntax::Trigger>(std::make_unique<Syntax::Number>(), std::bind(&DeviceCaptureReader::LedCaptureEndValue, this))),
	ledCaptureClose(std::make_unique<Syntax::Keyword>(L"]")),
	deviceEnumClose(std::make_unique<Syntax::Keyword>(L"]")),
	end(std::make_unique<Syntax::Any>())
{
	root.Connect(&allDevice);
	root.Connect(&device);
	root.Connect(&deviceEnumOpen);
	deviceEnumOpen.Connect(&device);
	device.Connect(&deviceCaptureOpen);
	deviceCaptureOpen.Connect(&deviceCaptureValue);
	deviceCaptureValue.Connect(&deviceCaptureValueEnumSeparator);
	deviceCaptureValueEnumSeparator.Connect(&deviceCaptureValue);
	deviceCaptureValue.Connect(&deviceCaptureValueRangeSeparator);
	deviceCaptureValueRangeSeparator.Connect(&deviceCaptureRangeEndValue);
	deviceCaptureRangeEndValue.Connect(&deviceCaptureClose);
	deviceCaptureValue.Connect(&deviceCaptureClose);
	deviceCaptureClose.Connect(&deviceSeparator);
	deviceSeparator.Connect(&device);
	deviceCaptureClose.Connect(&deviceEnumClose);
	deviceCaptureClose.Connect(&ledCaptureOpen);
	ledCaptureOpen.Connect(&ledCaptureValue);
	ledCaptureValue.Connect(&ledCaptureValueEnumSeparator);
	ledCaptureValue.Connect(&ledCaptureValueRangeSeparator);
	ledCaptureValueEnumSeparator.Connect(&ledCaptureValue);
	ledCaptureValueRangeSeparator.Connect(&ledCaptureRangeEndValue);
	ledCaptureRangeEndValue.Connect(&ledCaptureClose);
	ledCaptureValue.Connect(&ledCaptureClose);
	ledCaptureClose.Connect(&deviceEnumClose);
	ledCaptureClose.Connect(&deviceSeparator);
	ledCaptureClose.Connect(&end);
	allDevice.Connect(&end);
	device.Connect(&end);
	deviceCaptureClose.Connect(&end);
	deviceEnumClose.Connect(&end);
}
std::vector<DeviceCapture::CaptureUnit> DeviceCaptureReader::operator()(Syntax::Cursor& it)
{
	result.unit.clear();
	cursor = it;
	Syntax::TokenNode* x = &root;
	cursor.NextData();
	for (; !(cursor.AtEnd() || x == &end); cursor.NextData())
	{
		auto found = std::find_if(x->next.begin(), x->next.end(), std::bind(&DeviceCaptureReader::ProcessNode, this, std::placeholders::_1));
		if (found == x->next.end())
			throw ParsingError(L"Parsing error in DeviceCaptureReader.", cursor.Str(), cursor.Position());

		x = *found;
	}
	it = cursor;
	return result.unit;
}