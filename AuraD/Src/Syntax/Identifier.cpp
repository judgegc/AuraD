#include "Identifier.h"
namespace Syntax {
std::wstring Identifier::Value()
{
	return std::wstring(begin, end);
}
void Identifier::Process(Cursor & cursor)
{
	success = false;
	begin = cursor.pos;

	if (!iswalpha(*begin))
		return;

	++cursor.pos;

	while (!cursor.AtEnd() && (iswalpha(*cursor.pos) || iswdigit(*cursor.pos)))
		++cursor.pos;

	end = cursor.pos;
	success = true;
}
bool Identifier::Success()
{
	return success;
}
}