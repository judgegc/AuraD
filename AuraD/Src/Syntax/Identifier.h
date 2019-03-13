#pragma once
#include "Token.h"
#include <string>
namespace Syntax {
class Identifier: public Token
{
	std::wstring::const_iterator begin;
	std::wstring::const_iterator end;
	bool success;
public:
	std::wstring Value();
	virtual void Process(Cursor& cursor) override;
	virtual bool Success() override;
};
}
