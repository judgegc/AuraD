#include "AutoIncrement.h"
namespace Core
{
AutoIncrement::AutoIncrement(): next(0)
{
}
uint64_t AutoIncrement::Gen()
{
	return next++;
}
}
