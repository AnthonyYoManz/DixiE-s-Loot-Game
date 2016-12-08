#include "RecoilReductionPerk.h"

void RecoilReductionPerk::initialise(int _value, int _droprate, int _maxStacks)
{
	Perk::initialise(_value, _droprate, _maxStacks);
	m_name = "Recoil Reduction Perk";
	m_statsMod.m_recoil = -0.25;
}
