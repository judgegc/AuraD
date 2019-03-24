#include "Core/Exception.h"
#include "CommandLineReader.h"
#include "Application.h"

#include "Services/LoggerService.h"
#include "Log/FileLogger.h"

#include <io.h>
#include <atomic>
#include <fcntl.h>
#include <iostream>
#include <Windows.h>

using namespace Core;
using namespace Services;

std::atomic<bool> IsWorking = true;
BOOL WINAPI OnSignal(DWORD signal)
{
	if (signal == CTRL_C_EVENT)
	{
		IsWorking = false;
		return TRUE;
	}

	return FALSE;
}

int wmain(int argc, wchar_t *argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	SetConsoleCtrlHandler(OnSignal, TRUE);
	int exitCode = EXIT_SUCCESS;
	try
	{
		LoggerService::Initialize<Log::FileLogger>(L"activity.log");
		LoggerService::Instance()->Log(L"Logger initialized");

		CommandLineReader cmd;
		Application app(cmd(argc, argv));
		app.Run();
	}
	catch (const Exception& e)
	{
		std::wcerr << e.What() << std::endl;
		LoggerService::Instance()->Log(e.What());

		exitCode = EXIT_FAILURE;
	}
	catch (const std::exception& e)
	{
		std::string_view msg(e.what());
		std::wstring wmsg(msg.length(), 0);
		std::copy(msg.begin(), msg.end(), wmsg.begin());

		std::wcerr << wmsg << std::endl;
		LoggerService::Instance()->Log(wmsg);

		exitCode = EXIT_FAILURE;
	}

	LoggerService::Instance()->Log(L"Exited");

	return exitCode;
}