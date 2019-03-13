#pragma once
#include "Cursor.h"
namespace Syntax {
struct Token
{
	virtual void Process(Cursor& cursor) = 0;
	virtual bool Success() = 0;
	virtual ~Token() = default;
};
}