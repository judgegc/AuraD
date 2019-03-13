#pragma once
#include "Subprogram.h"

#include <Windows.h>
#include <Pdh.h>
class PdhDialog : public Subprogram
{
public:
	virtual void Run() override;
private:
	void CheckErrors();
private:
	PDH_STATUS status;
};