#pragma once
#include "Syntax/TokenNode.h"

#include "Syntax/Cursor.h"

class RangeReader
{
public:
	struct Range
	{
		int64_t start;
		int64_t stop;
	};
	RangeReader();
	Range operator()(Syntax::Cursor& it);
private:
	bool ProcessNode(Syntax::TokenNode* node);
private:
	Syntax::Cursor cursor;

	Syntax::TokenNode root;
	Syntax::TokenNode openBracket;
	Syntax::TokenNode closeBracket;
	Syntax::TokenNode startValue;
	Syntax::TokenNode separator;
	Syntax::TokenNode stopValue;
	Syntax::TokenNode end;
};
