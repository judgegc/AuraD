#include "Keyword.h"
namespace Syntax {
Keyword::Keyword(const std::wstring & keyword): value(keyword){}

void Keyword::Process(Cursor & cursor)
{
	std::wstring::const_iterator old = cursor.pos;
	while (!cursor.AtEnd() && static_cast<size_t>(cursor.pos - old) < value.length())
		++cursor.pos;

	success = value == std::wstring(old, cursor.pos)/* && (cursor.AtEnd() || !isalpha(*cursor.x) && !isdigit(*cursor.x))*/;
	if (!success)
		cursor.pos = old;
}

bool Keyword::Success()
{
	return success;
}
}
