#pragma once
#include <string>
namespace Provider
{
struct SourceInfo
{
	enum class Schema { PDH };
	Schema protocol;
	std::wstring source;
};
}
