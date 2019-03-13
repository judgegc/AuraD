#pragma once
#include "Rgb.h"
#include "AuraSDK/Color.h"
#include "ColorModel.h"
namespace ColorSchema {
struct AuraModelAdapter
{
	virtual operator AuraSDK::Color() = 0;

};
}