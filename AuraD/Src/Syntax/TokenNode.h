#pragma once
#include "Token.h"
#include "Trigger.h"
#include <vector>
#include <memory>
namespace Syntax {
struct TokenNode
{
	std::unique_ptr<Token> t;
	std::vector<TokenNode*> next;
	TokenNode(std::unique_ptr<Token> token);
	void Connect(TokenNode* to);
	template<typename R>
	inline R* Get()
	{
		if (Trigger* tp = dynamic_cast<Trigger*>(t.get()))
		{
			for (; auto a = dynamic_cast<Trigger*>(tp->t.get()); tp = a);
			return dynamic_cast<R*>(tp->t.get());
		}
		else
		{
			return dynamic_cast<R*>(t.get());
		}
	}
};
}