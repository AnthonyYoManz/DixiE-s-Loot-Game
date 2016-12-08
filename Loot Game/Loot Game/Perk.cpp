#include "Perk.h"
#include <map>

std::vector<PerkRegistration> Perk::registeredPerks;
int Perk::totalDroprates = 0;

std::vector<Perk*> Perk::getPerks(int _maxTotalValue)
{
	std::vector<Perk*> perks;
	int availablePoints = _maxTotalValue;
	std::map<int, Perk*> perkMap;
	while (availablePoints > 0)
	{
		int rng = rand() % Perk::totalDroprates;
		int iterationValue = 0;
		for (auto& perk : registeredPerks)
		{
			iterationValue += perk.m_droprate;
			if (rng < iterationValue)
			{
				int projectedPoints = availablePoints - perk.m_value;
				if (projectedPoints >= 0)
				{
					if (perkMap.find(iterationValue) != perkMap.end())
					{
						Perk* cPerk = perkMap[iterationValue];
						if (cPerk->getMaxStackCount() > cPerk->getStackCount() || cPerk->getMaxStackCount() <= 0)
						{
							cPerk->stack();
						}
						else
						{
							break;
						}
					}
					else
					{
						perks.push_back(perk.m_creator());
						perkMap[iterationValue] = perks.back();
					}
				}
				availablePoints = projectedPoints;
			}
		}
	}

	return perks;
}

void Perk::initialise(int _value, int _droprate, int _maxStacks)
{
	m_name = "Unnamed Perk";
	m_value = _value;
	m_droprate = _droprate;
	m_stackCount = 1;
	m_maxStacks = _maxStacks;
	m_statsMod.m_aimGuide = false;
	m_statsMod.m_ammoPerProjectile = +0;
	m_statsMod.m_attackCooldown = +0;
	m_statsMod.m_automatic = false;
	m_statsMod.m_chargeTime = +0;
	m_statsMod.m_clipSize = +0;
	m_statsMod.m_damage = +0;
	m_statsMod.m_despreadRate = +0;
	m_statsMod.m_maxSpread = +0;
	m_statsMod.m_minSpread = +0;
	m_statsMod.m_projectileSpeed = +0;
	m_statsMod.m_projectilesPerShot = +0;
	m_statsMod.m_range = +0;
	m_statsMod.m_recoil = +0;
	m_statsMod.m_reloadTime = +0;
	m_statsMod.m_shotCooldown = +0;
	m_statsMod.m_shotsPerTrigger = +0;
	m_statsMod.m_spreadRate = +0;
}

void Perk::stack(int _stacks)
{
	m_stackCount += _stacks;
	if (m_stackCount > m_maxStacks && m_maxStacks > 0)
	{
		m_stackCount = m_maxStacks;
	}
}

WeaponStats Perk::getStatsMod() const
{
	return m_statsMod;
}

int Perk::getMaxStackCount() const
{
	return m_maxStacks;
}

int Perk::getStackCount() const
{
	return m_stackCount;
}

int Perk::getValue() const
{
	return m_value;
}

int Perk::getDroprate() const
{
	return m_droprate;
}

std::string Perk::getRawName() const
{
	return m_name;
}

std::string Perk::getName() const
{
	if (m_stackCount <= 1) 
	{
		return m_name;
	}
	return m_name + " *" + std::to_string(m_stackCount);
}
