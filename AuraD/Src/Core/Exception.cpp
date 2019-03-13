#include "Exception.h"
namespace Core {
Exception::Exception(const std::wstring & msg) : msg(msg) {}

const std::wstring Exception::What() const
{
	return msg;
}
}