#pragma once
#include "Core/Exception.h"

#include <string>
class ParsingError : public Core::Exception
{
public:
	explicit ParsingError(const std::wstring& title, const std::wstring& sample, size_t problemIdx);
private:
	std::wstring Format(const std::wstring& title, const std::wstring& sample, size_t problemIdx) const;
};
