#include "Cursor.h"
#include <algorithm>
namespace Syntax {
Cursor::Cursor(const std::wstring* target) : target(target), pos(target->begin()) {}
bool Cursor::AtEnd()
{
	return pos == target->end();
}
void Cursor::NextData()
{
	while (!AtEnd() && *pos == ' ')
		++pos;
}
size_t Cursor::Position() const
{
	return std::distance(target->begin(), pos);
}
std::wstring Cursor::Str() const
{
	return std::wstring(target->data() + Position());
}
}
