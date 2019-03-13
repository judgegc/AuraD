#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
struct CommandLineReader
{
	std::unordered_map<std::wstring, std::vector<std::wstring>> operator()(int argc, wchar_t *argv[]) const;
};
