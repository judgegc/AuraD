#pragma once
#include <string>
#include <ctime>
namespace Core
{
void Utf16ToUtf8(wchar_t code, std::array<uint8_t, 5>& out);
std::string Utf16ToUtf8(const std::wstring& str);
std::tm localtime_xp(std::time_t timer);
std::wstring Timestamp(const std::wstring& fmt = L"%F %T");
}