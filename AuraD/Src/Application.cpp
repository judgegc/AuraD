#include "Application.h"
#include "Subprogram.h"
#include "PdhDialog.h"
#include "DynamicBacklight.h"
#include "Core/Exception.h"

#include <memory>
Application::Application(const std::unordered_map<std::wstring, std::vector<std::wstring>>& options) : options(options)
{
}

void Application::Run()
{
	std::unique_ptr<Subprogram> module;
	if (auto pdhOpts = options.find(L"p"); pdhOpts != options.end())
	{
		module = std::make_unique<PdhDialog>();
	}
	else if (auto backlightOptions = options.find(L"e"); backlightOptions != options.end())
	{
		module = std::make_unique<DynamicBacklight>(backlightOptions->second);
	}
	else
	{
		throw Core::Exception(L"No options provided.");
	}

	module->Run();
}
