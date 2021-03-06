#pragma once
#include "Token.h"
namespace Syntax {
class Any : public Token
{
public:
	virtual void Process(Cursor& cursor) override;
	virtual bool Success() override;
};
}