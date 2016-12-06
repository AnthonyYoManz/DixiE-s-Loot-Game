#pragma once
#include "ItemObject.h"
#include "WeaponObject.h"

enum class EquipSlot
{
	LEFT_HAND,
	RIGHT_HAND
};

class Equipment
{
private:
	WeaponObject* m_leftHand;
	WeaponObject* m_rightHand;
public:
	Equipment();
	//Returns previously equipped weapon or nullptr if there were none
	WeaponObject* equip(WeaponObject* _weapon, EquipSlot _slot);
	WeaponObject* unequip(EquipSlot _slot);
	WeaponObject* getLeftHand();
	WeaponObject* getRightHand();
};