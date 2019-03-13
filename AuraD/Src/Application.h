#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Application
{
public:
	explicit Application(const std::unordered_map<std::wstring, std::vector<std::wstring>>& options);
	void Run();
private:
	std::unordered_map<std::wstring, std::vector<std::wstring>> options;
};
