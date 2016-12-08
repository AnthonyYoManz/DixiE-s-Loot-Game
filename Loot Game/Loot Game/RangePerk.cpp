#include "RangePerk.h"

void RangePerk::initialise(int _value, int _droprate, int _maxStacks)
{
	Perk::initialise(_value, _droprate, _maxStacks);
	m_name = "Range Perk";
	m_statsMod.m_range = +5;
}
