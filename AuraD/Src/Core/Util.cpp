#include "Util.h"
#include <array>
#include <algorithm>
namespace Core {
/*
https://stackoverflow.com/questions/23502153/utf-8-encoding-algorithm-vs-utf-16-algorithm
*/
void Utf16ToUtf8(wchar_t code, std::array<uint8_t, 5>& out)
{
	if (code <= 0x7F)
	{
		out[0] = static_cast<uint8_t>(code & 0x7F);
		out[1] = '\0';
	}
	else if (code > 0x10FFFF)
	{
		// unicode replacement character
		std::array<uint8_t, 3> pattern = { 0xEF, 0xBF, 0xBD };
		std::copy(pattern.begin(), pattern.end(), out.begin());
	}
	else
	{
		int count;
		if (code <= 0x7FF) {
			// one continuation byte
			count = 1;
		}
		else if (code <= 0xFFFF) {
			// two continuation bytes
			count = 2;
		}
		else {
			// three continuation bytes
			count = 3;
		}
		for (int i = 0; i < count; ++i) {
			out[count - i] = 0x80 | (code & 0x3F);
			code >>= 6;
		}
		out[0] = (0x1E << (6 - count)) | (code & (0x3F >> count));
		out[1 + count] = '\0';
	}
}

std::string Utf16ToUtf8(const std::wstring& str)
{
	std::string ret;
	for (wchar_t c : str)
	{
		std::array<uint8_t, 5> utf8Char;
		Utf16ToUtf8(c, utf8Char);
		auto endIdx = std::distance(utf8Char.begin(), std::find(utf8Char.begin(), utf8Char.end(), '\0'));
		std::copy_n(utf8Char.begin(), endIdx, back_inserter(ret));
	}
	return ret;
}

}