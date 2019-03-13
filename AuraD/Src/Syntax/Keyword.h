#pragma once
#include "Token.h"
#include <string>
namespace Syntax {
class Keyword: public Token
{
	bool success;
	std::wstring value;
public:
	Keyword(const std::wstring &keyword);
	virtual void Process(Cursor& cursor) override;
	virtual bool Success() override;
};
}
