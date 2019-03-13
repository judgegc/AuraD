#pragma once
#include "Token.h"
#include <string>
#include <functional>
#include <memory>
namespace Syntax {
class Trigger : public Token
{
public:
	std::unique_ptr<Token> t;
	std::function<void(void)> action;
public:
	explicit Trigger(std::unique_ptr<Token> t, std::function<void(void)> action);
	virtual void Process(Cursor& cursor) override;
	virtual bool Success() override;
};
}
