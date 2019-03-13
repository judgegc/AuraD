#include "QuotedString.h"

namespace DataSource
{
void QuoutedString::Process(Syntax::Cursor & cursor)
{
	begin = cursor.pos;
	while (!cursor.AtEnd() && *cursor.pos != L'\'') ++cursor.pos;
	end = cursor.pos;
	success = !cursor.AtEnd();
	if (!success)
		cursor.pos = begin;
}
bool QuoutedString::Success()
{
	return success;
}
std::wstring QuoutedString::Uri() const
{
	return std::wstring(begin, end);
}
}
