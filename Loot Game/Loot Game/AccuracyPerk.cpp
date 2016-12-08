#include "AccuracyPerk.h"


void AccuracyPerk::initialise(int _value, int _droprate, int _maxStacks)
{
	Perk::initialise(_value, _droprate, _maxStacks);
	m_name = "Accuracy Perk";
	m_statsMod.m_maxSpread = -0.5;
	m_statsMod.m_minSpread = -0.5;
}
