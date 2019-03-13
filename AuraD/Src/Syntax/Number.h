#pragma once
#include "Token.h"
#include <string>
namespace Syntax {
class Number : public Token
{
	double value;
	bool success;
public:
	double Value();
	virtual void Process(Cursor& cursor) override;
	virtual bool Success() override;
};
}