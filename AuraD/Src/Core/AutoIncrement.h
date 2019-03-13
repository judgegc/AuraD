#pragma once
#include <cstdint>
namespace Core {
class AutoIncrement
{
public:
	AutoIncrement();
	uint64_t Gen();
public:
	using ValueType = uint64_t;
private:
	uint64_t next;
};
}
