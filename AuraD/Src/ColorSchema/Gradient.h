#pragma once
#include "AuraSDK/Color.h"
#include <map>
#include <string>
#include <memory>
namespace ColorSchema
{
class Gradient
{
public:
	using Offset = double;
	using ColorTransition = std::map<Offset, AuraSDK::Color>;
	Gradient() = default;
	explicit Gradient(const ColorTransition& colorMap);
	void SetTransition(const ColorTransition& colorMap);
	void AddStopColor(AuraSDK::Color color, Offset offset);
	AuraSDK::Color Get(Offset offset) const;
	virtual ~Gradient() = default;
private:
	virtual Offset Transform(Offset offset) const = 0;
	static AuraSDK::Color Interpolate(AuraSDK::Color begin, AuraSDK::Color end, Offset o);
	ColorTransition transitionMap;
};
}