#include "Core/Exception.h"
#include "CommandLineReader.h"
#include "Application.h"

#include <io.h>
#include <atomic>
#include <fcntl.h>
#include <iostream>
#include <Windows.h>

using namespace Core;

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

	try
	{
		CommandLineReader cmd;
		Application app(cmd(argc, argv));
		app.Run();
	}
	catch (const Exception& e)
	{
		std::wcerr << e.What() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::wcerr << e.what() << std::endl;
	}
	return 0;
}