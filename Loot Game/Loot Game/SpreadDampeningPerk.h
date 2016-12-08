#pragma once
#include "Perk.h"

class SpreadDampeningPerk : public Perk
{
public:
	void initialise(int _value, int _droprate, int _maxStacks) override;
};