#include "BattleUnitStack.h"

#include "Data.h"

BattleUnitStack::BattleUnitStack(const UnitStack& t) :
	base(&(Data::get()->unit[t.getType()])), maxSize(t.getNumber()),
	curSize(maxSize), stat(base->stat) { }

void BattleUnitStack::setStat(uint8_t number, float value) {
	stat[number] = value;
}
void BattleUnitStack::shiftStat(uint8_t number, float value) {
	stat[number] += value;
}

void BattleUnitStack::applyStatusEffect(StatusEffect&& effect) {
	if (effect.getDuration()) {
		
	}
	else {

	}
//	for (uint8_t i = 0; i < effect.statList.size(); ++i)
//		shiftStat(effect.statList[i].name, effect.statList[i].value);
//	if (effect.getDuration())
//		status.emplace_back(effect); 
}
void BattleUnitStack::useSkill(uint8_t skillNumber, BattleUnitStack& target){
	const UnitSkill& skill = Data::get()->unitSkill[base->skill[skillNumber]];
	for (uint8_t i = 0; i < skill.effect.size(); ++i) {
		std::vector<StatusEffect::Effect> effect;
		const UnitStatModifier& mod = Data::get()->unitStatModifier[skill.effect[i].ID];
		for (uint8_t j = 0; j < mod.effect.size(); ++j)
			effect.emplace_back(StatusEffect::Effect(mod.effect[i].stat, mod.effect[i].action, mod.effect[i].count(getStatVector(), target.getStatVector())));
		if (skill.effect[i].target == 'u')
			applyStatusEffect(StatusEffect(mod.name, mod.priority, skill.effect[i].duration, effect));
		if (skill.effect[i].target == 't')
			target.applyStatusEffect(StatusEffect(mod.name, mod.priority, skill.effect[i].duration, effect));
	}
}

