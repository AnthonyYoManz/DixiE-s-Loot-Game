#pragma once

struct WeaponStats
{
	//Automatic
	bool m_automatic;

	//For burst fire
	int m_shotsPerTrigger;
	int m_shotCooldown;

	//Damage per hit
	float m_damage;

	//Rate of fire
	int m_attackCooldown;

	//Time after clicking before gun fires
	int m_chargeTime;

	//Spread/Spray params
	float m_maxSpread;
	float m_minSpread;
	float m_spreadRate;
	float m_despreadRate;

	//Power of recoil
	float m_recoil;

	//Ammo params
	int m_clipSize;
	int m_ammoPerProjectile;
	int m_reloadTime;

	//Weapon Range
	int m_range;

	//Speed at which projectiles travel
	int m_projectileSpeed;

	//Draw spread lines
	bool m_aimGuide;

	//For shotguns and maybe more
	int m_projectilesPerShot;
};