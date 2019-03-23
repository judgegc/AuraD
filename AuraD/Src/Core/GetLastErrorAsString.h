#pragma once
#include "Exception.h"

#include <Windows.h>
#include <string>
#include <string_view>
#include <exception>
namespace Core {
std::wstring GetLastErrorAsString(const std::wstring& source = L"");
}
