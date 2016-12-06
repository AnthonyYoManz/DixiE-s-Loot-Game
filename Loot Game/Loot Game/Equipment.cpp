#include "Equipment.h"

Equipment::Equipment()
{
	m_leftHand = nullptr;
	m_rightHand = nullptr;
}

WeaponObject* Equipment::equip(WeaponObject * _weapon, EquipSlot _slot)
{
	WeaponObject* prevWeapon = nullptr;
	if (_slot == EquipSlot::LEFT_HAND && (m_rightHand || !m_leftHand))
	{
		prevWeapon = m_leftHand;
		m_leftHand = _weapon;
	}
	else
	{
		prevWeapon = m_rightHand;
		m_rightHand = _weapon;
	}
	return prevWeapon;
}

WeaponObject* Equipment::unequip(EquipSlot _slot)
{
	WeaponObject* prevWeapon = nullptr;
	if (_slot == EquipSlot::LEFT_HAND)
	{
		if (m_leftHand)
		{
			prevWeapon = m_leftHand;
			m_leftHand->unequip();
			m_leftHand = nullptr;
		}
	}
	else
	{
		if (m_rightHand)
		{
			prevWeapon = m_rightHand;
			m_rightHand->unequip();
			m_rightHand = nullptr;
		}
	}
	return prevWeapon;
}

WeaponObject* Equipment::getLeftHand()
{
	return m_leftHand;
}

WeaponObject* Equipment::getRightHand()
{
	return m_rightHand;
}
