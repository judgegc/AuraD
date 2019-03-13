#pragma once
#include "Syntax/Cursor.h"
#include "Syntax/Identifier.h"
#include "Syntax/Keyword.h"
#include "Syntax/Number.h"
#include "Syntax/Trigger.h"
#include "Syntax/TokenNode.h"
#include "Syntax/Any.h"

#include "DeviceCapture/CaptureUnit.h"

#include <string>
#include <memory>
#include <functional>
class DeviceCaptureReader
{
	Syntax::Cursor cursor;
	Syntax::TokenNode root;
	Syntax::TokenNode allDevice;
	Syntax::TokenNode device;
	Syntax::TokenNode deviceEnumOpen;
	Syntax::TokenNode deviceCaptureOpen;
	Syntax::TokenNode deviceCaptureValue;
	Syntax::TokenNode deviceCaptureValueEnumSeparator;
	Syntax::TokenNode deviceCaptureValueRangeSeparator;
	Syntax::TokenNode deviceCaptureRangeEndValue;
	Syntax::TokenNode deviceCaptureClose;
	Syntax::TokenNode deviceSeparator;
	Syntax::TokenNode ledCaptureOpen;
	Syntax::TokenNode ledCaptureValue;
	Syntax::TokenNode ledCaptureValueEnumSeparator;
	Syntax::TokenNode ledCaptureValueRangeSeparator;
	Syntax::TokenNode ledCaptureRangeEndValue;
	Syntax::TokenNode ledCaptureClose;
	Syntax::TokenNode deviceEnumClose;
	Syntax::TokenNode end;

	struct
	{
		std::vector<DeviceCapture::CaptureUnit> unit;
	}result;
private:
	bool ProcessNode(Syntax::TokenNode* node);
	void NewUnit();
	void NewAllUnit();
	void DeviceCapturedValue();
	void DevicecaptureEndValue();
	void LedCapturedValue();
	void LedCaptureEndValue();
	void DeviceRangeMode();
	void LedRangeMode();
public:
	DeviceCaptureReader();
	std::vector<DeviceCapture::CaptureUnit> operator()(Syntax::Cursor& it);
};
