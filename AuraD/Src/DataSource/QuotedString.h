#pragma once
#include "Syntax/Token.h"
#include <string>

namespace DataSource
{
class QuoutedString : public Syntax::Token
{
	std::wstring::const_iterator begin;
	std::wstring::const_iterator end;
	bool success;
public:
	virtual void Process(Syntax::Cursor& cursor) override;
	virtual bool Success() override;
	std::wstring Uri() const;
};
}
