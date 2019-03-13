#include "Gradient.h"
#include "Factory.h"
#include <iterator>
#include <cctype>
#include <exception>
#include <unordered_map>

namespace ColorSchema {
Gradient::Gradient(const ColorTransition & colorMap) : transitionMap(colorMap)
{
}
void Gradient::SetTransition(const ColorTransition & colorMap)
{
	transitionMap = colorMap;
}
void Gradient::AddStopColor(AuraSDK::Color color, Offset offset)
{
	transitionMap.emplace(std::make_pair(offset, color));
}
AuraSDK::Color Gradient::Get(Offset offset) const
{
	Offset to = Transform(offset);
	auto rit = transitionMap.upper_bound(to);

	if (rit == transitionMap.end())
		return transitionMap.rbegin()->second;

	auto lit = std::prev(rit);
	Offset rel = (to - lit->first) / (rit->first - lit->first);
	return Interpolate(lit->second, rit->second, rel);
}
AuraSDK::Color Gradient::Interpolate(AuraSDK::Color begin, AuraSDK::Color end, Offset o)
{
	int rd = end.Red() - begin.Red();
	int gd = end.Green() - begin.Green();
	int bd = end.Blue() - begin.Blue();
	return AuraSDK::Color(begin.Red() + rd * o, begin.Green() + gd * o, begin.Blue() + bd * o);
}
}