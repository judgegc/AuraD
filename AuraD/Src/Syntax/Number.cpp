#include "Number.h"
namespace Syntax {
double Number::Value()
{
	return value;
}
void Number::Process(Cursor & cursor)
{
	try
	{
		size_t read;
		value = std::stod(cursor.Str(), &read);
		cursor.pos += read;
		success = true;
	}
	catch (const std::invalid_argument&)
	{
		success = false;
	}
	catch (const std::out_of_range&)
	{
		success = false;
	}
}
bool Number::Success()
{
	return success;
}
}