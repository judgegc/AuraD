#include "NonQuotedString.h"
namespace DataSource
{
void NonQuotedString::Process(Syntax::Cursor & cursor)
{
	begin = cursor.pos;
	while (!cursor.AtEnd() && *cursor.pos++ != L' ');
	end = cursor.pos;
	success = true;
}
bool NonQuotedString::Success()
{
	return success;
}
std::wstring NonQuotedString::Uri() const
{
	return std::wstring(begin, end);
}
}