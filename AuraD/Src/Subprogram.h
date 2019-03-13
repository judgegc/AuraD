#pragma once
class Subprogram
{
public:
	virtual void Run() = 0;
	virtual ~Subprogram() = default;
};