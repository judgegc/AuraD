#include "ParsingError.h"

#include <sstream>
#include <iomanip>
ParsingError::ParsingError(const std::wstring& title, const std::wstring& sample, size_t problemIdx): Core::Exception(Format(title, sample, problemIdx))
{
}

std::wstring ParsingError::Format(const std::wstring& title, const std::wstring& sample, size_t problemIdx) const
{
	std::wstringstream msg;
	msg << title << L'\n';
	msg << sample << L" at position " << problemIdx << L".\n";
	msg << std::setw(problemIdx + 1) << '^' << std::endl;
	return msg.str();
}
