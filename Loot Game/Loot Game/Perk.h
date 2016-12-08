#pragma once
#include "WeaponStats.h"
#include <vector>
#include <functional>
#include <string>

class Perk;

struct PerkRegistration
{
	std::function<Perk*()> m_creator;
	int m_value;
	int m_droprate;
};

class Perk
{
private:
	static std::vector<PerkRegistration> registeredPerks;
	static int totalDroprates;
protected:
	std::string m_name;
	int m_value;
	int m_droprate;
	int m_stackCount;
	int m_maxStacks;
	WeaponStats m_statsMod;
public:
	static void initialisePerkSystem();
	template <typename T>
	static void registerPerkCreator(int _perkValue, int _droprate, int _maxStacks);
	static std::vector<Perk*> getPerks(int _maxTotalValue);

	virtual void initialise(int _value, int _droprate, int _maxStacks);

	void stack(int _stacks = 1);

	WeaponStats getStatsMod() const;
	//Buff* getBuff() const;
	int getMaxStackCount() const;
	int getStackCount() const;
	int getValue() const;
	int getDroprate() const;
	std::string getRawName() const;
	std::string getName() const;
};

template<typename T>
inline void Perk::registerPerkCreator(int _perkValue, int _droprate, int _maxStacks)
{
	PerkRegistration registration;
	registration.m_creator = [_perkValue, _droprate, _maxStacks]()
	{
		Perk* perk = new T;
		perk->initialise(_perkValue, _droprate, _maxStacks);
		return perk;
	};
	registration.m_droprate = _droprate;
	registration.m_value = _perkValue;
	totalDroprates += _droprate;
	Perk::registeredPerks.push_back(registration);
}
