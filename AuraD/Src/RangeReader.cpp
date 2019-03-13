#include "RangeReader.h"
#include "Core/Exception.h"

#include "Syntax/Keyword.h"
#include "Syntax/Number.h"
#include "Syntax/Any.h"

#include "ParsingError.h"

#include <memory>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <functional>

RangeReader::RangeReader() :
	root(nullptr),
	openBracket(std::make_unique<Syntax::Keyword>(L"[")),
	startValue(std::make_unique<Syntax::Number>()),
	separator(std::make_unique<Syntax::Keyword>(L":")),
	stopValue(std::make_unique<Syntax::Number>()),
	closeBracket(std::make_unique<Syntax::Keyword>(L"]")),
	end(std::make_unique<Syntax::Any>())
{
	root.Connect(&openBracket);
	openBracket.Connect(&startValue);
	startValue.Connect(&separator);
	separator.Connect(&stopValue);
	stopValue.Connect(&closeBracket);
}

RangeReader::Range RangeReader::operator()(Syntax::Cursor & it)
{
	cursor = it;
	Syntax::TokenNode* x = &root;
	cursor.NextData();
	for (; !(cursor.AtEnd() || x == &end); cursor.NextData())
	{
		auto found = std::find_if(x->next.begin(), x->next.end(), std::bind(&RangeReader::ProcessNode, this, std::placeholders::_1));
		if (found == x->next.end())
			throw ParsingError(L"Parsing error in RangeReader", cursor.Str(), cursor.Position());

		x = *found;
	}
	it = cursor;
	return { static_cast<int64_t>(startValue.Get<Syntax::Number>()->Value()) ,static_cast<int64_t>(stopValue.Get<Syntax::Number>()->Value()) };
}

bool RangeReader::ProcessNode(Syntax::TokenNode * node)
{
	node->t->Process(cursor);
	return node->t->Success();
}
