#pragma once
#include <string>
namespace Core {
class Exception
{
	std::wstring msg;
public:
	explicit Exception(const std::wstring& msg);
	const std::wstring What() const;
	virtual ~Exception() = default;
};
}