#include "CommandLineReader.h"
#include "Core/Exception.h"
#include <algorithm>

std::unordered_map<std::wstring, std::vector<std::wstring>> CommandLineReader::operator()(int argc, wchar_t * argv[]) const
{
	std::unordered_map<std::wstring, std::vector<std::wstring>> opts;
	const wchar_t OptPrefix = L'-';
	bool optReady = false;
	std::wstring option;
	for (size_t n = 1; n < argc; ++n)
	{
		std::wstring str(argv[n]);
		if (/*!optReady &&*/ str.size() >= 2 && str.front() == OptPrefix)
		{
			bool full = str[1] == OptPrefix;
			option = std::wstring(str.begin() + (full ? 2 : 1), str.end());

			opts[option];
			optReady = true;
		}
		else if (optReady)
		{
			opts[option].push_back(str);
			optReady = false;
		}
		else
		{
			throw Core::Exception(L"Option key not found");
		}
	}
	return opts;
}
