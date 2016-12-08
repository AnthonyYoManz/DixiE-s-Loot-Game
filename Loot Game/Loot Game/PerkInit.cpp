#include "Perk.h"
#include "SprayPerk.h"
#include "AccuracyPerk.h"
#include "BurstPerk.h"
#include "RangePerk.h"
#include "SpreadDampeningPerk.h"
#include "RecoilReductionPerk.h"

void Perk::initialisePerkSystem()
{
	//Spray Perk: Value 1, droprate 1, max stacks -1 (unlimited)
	Perk::registerPerkCreator<SprayPerk>(1, 1, -1);

	//Accuracy Perk: Value 1, droprate 1, max stacks -1 (unlimited)
	Perk::registerPerkCreator<AccuracyPerk>(1, 1, -1);

	//Burst Perk: Value 1, droprate 1, max stacks 1
	Perk::registerPerkCreator<BurstPerk>(1, 1, 1);

	//Range Perk: Value 1, droprate 1, max stacks -1 (unlimited)
	Perk::registerPerkCreator<RangePerk>(1, 1, -1);

	//Spread Dampening Perk: Value 1, droprate 1, max stacks -1 (unlimited)
	Perk::registerPerkCreator<SpreadDampeningPerk>(1, 1, -1);

	//Recoil Reduction Perk: Value 1, droprate 1, max stacks -1 (unlimited)
	Perk::registerPerkCreator<RecoilReductionPerk>(1, 1, -1);
}