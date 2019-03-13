#include "PdhDialog.h"
#include "Core/Exception.h"
#include "Core/GetLastErrorAsString.h"

#include <iostream>

void PdhDialog::Run()
{
	WCHAR CounterPathBuffer[PDH_MAX_COUNTER_PATH];
	PDH_BROWSE_DLG_CONFIG BrowseDlgData;
	ZeroMemory(&BrowseDlgData, sizeof(PDH_BROWSE_DLG_CONFIG));
	BrowseDlgData.bIncludeInstanceIndex = FALSE;
	BrowseDlgData.bSingleCounterPerAdd = FALSE;
	BrowseDlgData.bSingleCounterPerDialog = TRUE;
	BrowseDlgData.bLocalCountersOnly = FALSE;
	BrowseDlgData.bWildCardInstances = TRUE;
	BrowseDlgData.bHideDetailBox = TRUE;
	BrowseDlgData.bInitializePath = FALSE;
	BrowseDlgData.bDisableMachineSelection = FALSE;
	BrowseDlgData.bIncludeCostlyObjects = FALSE;
	BrowseDlgData.bShowObjectBrowser = FALSE;
	BrowseDlgData.hWndOwner = NULL;
	BrowseDlgData.szReturnPathBuffer = CounterPathBuffer;
	BrowseDlgData.cchReturnPathLength = PDH_MAX_COUNTER_PATH;
	BrowseDlgData.pCallBack = NULL;
	BrowseDlgData.dwCallBackArg = 0;
	BrowseDlgData.CallBackStatus = ERROR_SUCCESS;
	BrowseDlgData.dwDefaultDetailLevel = PERF_DETAIL_EXPERT;
	BrowseDlgData.szDialogBoxCaption = NULL;

	status = PdhBrowseCounters(&BrowseDlgData);
	CheckErrors();

	std::wcout << CounterPathBuffer << std::endl;
}

void PdhDialog::CheckErrors()
{
	using namespace Core;
	if (status != ERROR_SUCCESS)
		throw Exception(GetLastErrorAsString(L"pdh.dll"));
}
