#pragma once
#include "ColorModel.h"
#include "AuraModelAdapter.h"
namespace ColorSchema
{
class Rgb: public ColorModel
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
public:
	uint8_t Red() const;
	uint8_t Green() const;
	uint8_t Blue() const;
	virtual uint8_t Components() const override;
	virtual void SetComponent(uint8_t idx, double value) override;
};
}