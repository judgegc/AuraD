#pragma once
#include "AuraModelAdapter.h"
#include "Rgb.h"
namespace ColorSchema 
{
class RgbAdapter: public AuraModelAdapter
{
	const Rgb& target;
public:
	explicit RgbAdapter(const Rgb& target);
	virtual operator AuraSDK::Color() override;
	virtual ~RgbAdapter() = default;
};
}
