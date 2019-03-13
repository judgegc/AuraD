#include "TokenNode.h"
namespace Syntax {
TokenNode::TokenNode(std::unique_ptr<Token> token) : t(std::move(token)) {}
void TokenNode::Connect(TokenNode * to)
{
	next.push_back(to);
}
}