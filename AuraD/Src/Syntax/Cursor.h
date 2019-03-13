#pragma once
#include <string>
namespace Syntax {
struct Cursor
{
	std::wstring::const_iterator pos;
	const std::wstring* target;
	Cursor() = default;
	explicit Cursor(const std::wstring* target);
	bool AtEnd();
	void NextData();
	size_t Position() const;
	std::wstring Str() const;
};
}
