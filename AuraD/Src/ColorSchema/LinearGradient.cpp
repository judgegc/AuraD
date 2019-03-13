#include "LinearGradient.h"
namespace ColorSchema
{
LinearGradient::LinearGradient(const ColorTransition & colorMap) : Gradient(colorMap) {}
Gradient::Offset LinearGradient::Transform(Offset offset) const
{
	return offset;
}
}