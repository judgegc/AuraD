#pragma once
#include <string>
namespace Core
{
void Utf16ToUtf8(wchar_t code, std::array<uint8_t, 5>& out);
std::string Utf16ToUtf8(const std::wstring& str);
}