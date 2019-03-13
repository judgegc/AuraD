#pragma once
#include "Gradient.h"
namespace ColorSchema
{
class LinearGradient : public Gradient
{
public:
	LinearGradient() = default;
	explicit LinearGradient(const ColorTransition& colorMap);
private:
	virtual Offset Transform(Offset offset) const override;

};
}
