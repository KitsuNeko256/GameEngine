#include "BattleUnitStack.h"

#include <algorithm>

#include "Constants.h"
#include "Data.h"

BattleUnitStack::BattleUnitStack(const UnitStack& t, uint16_t _army, uint64_t timer) :
	base(&(Data::get()->unit[t.getType()])), maxSize(t.getNumber()), size(maxSize), stat(base->stat), army(_army),
	waitEnd(timer + Constants::get()->BATTLE_TIMER_TICK() / stat.get(Data::get()->unitStat.getIndex("Initiative"))),
	waitInitiative(stat.get(Data::get()->unitStat.getIndex("Initiative")))
	{ }

void BattleUnitStack::applyStatusEffect(StatusEffect&& effect) {
	if (effect.getDuration()) {
		std::vector<StatusEffect>::iterator it = std::lower_bound(status.begin(), status.end(), effect);
		if (it != status.end())
			status.insert(++it, effect);
		else status.insert(status.begin(), effect);
	}
	else {
		std::vector<StatusEffect::Effect> t = effect.getEffect();
		for (uint16_t i = 0; i < t.size(); ++i) {
			if (t[i].action == '=')
				stat.set(t[i].statID, t[i].value);
			else if (t[i].action == '+')
				stat.shift(t[i].statID, t[i].value);
			else if (t[i].action == '-')
				stat.shift(t[i].statID, -t[i].value);
			else if (t[i].action == '*')
				stat.mult(t[i].statID, t[i].value);
			else if (t[i].action == '/')
				stat.mult(t[i].statID, 1.0 / t[i].value);
		}
	}
	recountStats();
}

void BattleUnitStack::updateHP() {
	uint16_t HPID = Data::get()->unitStat.getIndex("HP");
	uint16_t MaxHPID = Data::get()->unitStat.getIndex("MAX HP");
	int HP = stat.get(HPID);
	int MaxHP = stat.get(MaxHPID);
	if (HP > MaxHP) {
		if (HP / MaxHP > maxSize - size) {
			size = maxSize;
			stat.set(HPID, MaxHP);
		}
		else {
			size += HP / MaxHP;
			stat.set(HPID, HP % MaxHP);
		}
	}
	else if (HP < 0) {
		HP *= -1;
		if (HP / MaxHP >= size - 1) {
			size = 0;
		}
		else {
			size -= 1 + HP / MaxHP;
			stat.set(HPID, MaxHP - (HP % MaxHP));
		}
	}
}

void BattleUnitStack::recountStats() {
	updateHP();

	for (uint16_t i = 0; i < Data::get()->unitStat.getVarStart(); ++i)
		stat.set(i, base->stat.get(i));
	for (uint16_t i = Data::get()->unitStat.getVarStart(); i < Data::get()->unitStat.getRangeStart(); i += 2)
		stat.set(i + 1, base->stat.get(i + 1));
	for (uint16_t i = Data::get()->unitStat.getRangeStart(); i < Data::get()->unitStat.getSize(); i += 3) {
		stat.set(i + 1, base->stat.get(i + 1));
		stat.set(i + 2, base->stat.get(i + 2));
	}

	for (uint16_t i = 0; i < status.size(); ++i) {
		std::vector<StatusEffect::Effect> t = status[i].getEffect();
		for (uint16_t j = 0; j < t.size(); ++j) {
			const StatusEffect::Effect& effect = t[j];
			if (Data::get()->unitStat.getVarStart() <= effect.statID && effect.statID < Data::get()->unitStat.getRangeStart() &&
				((effect.statID - Data::get()->unitStat.getVarStart()) % 2 == 0))
					continue;
			if (effect.action == '=')
				stat.set(effect.statID, effect.value);
			else if (effect.action == '+')
				stat.shift(effect.statID, effect.value);
			else if (effect.action == '-')
				stat.shift(effect.statID, -effect.value);
			else if (effect.action == '*')
				stat.mult(effect.statID, effect.value);	
			else if (effect.action == '/')
				stat.mult(effect.statID, 1.0 / effect.value);
		}
	}
	stat.mult(Data::get()->unitStat.getIndex("Damage"), size);
}

void BattleUnitStack::useSkill(uint16_t skillNumber, BattleUnitStack& target){
	const UnitSkill& skill = Data::get()->unitSkill[base->skill[skillNumber]];
	for (uint16_t i = 0; i < skill.effect.size(); ++i) {
		std::vector<StatusEffect::Effect> effect;
		const UnitStatModifier& mod = Data::get()->unitStatModifier[skill.effect[i].ID];
		for (uint16_t j = 0; j < mod.effect.size(); ++j)
			effect.emplace_back(StatusEffect::Effect(mod.effect[i].stat, mod.effect[i].action, mod.effect[i].count(stat, target.stat)));
		if (skill.effect[i].target == 'u')
			applyStatusEffect(StatusEffect(mod.name, mod.priority, skill.effect[i].duration, effect));
		if (skill.effect[i].target == 't')
			target.applyStatusEffect(StatusEffect(mod.name, mod.priority, skill.effect[i].duration, effect));
	}
}

void BattleUnitStack::wait() {
	waitEnd += Constants::get()->BATTLE_TIMER_TICK() / (waitInitiative * 2);
}
void BattleUnitStack::updateTimer(uint64_t timer) {
	waitEnd = (waitEnd - timer) * waitInitiative / stat.get(Data::get()->unitStat.getIndex("Initiative"));
	waitInitiative = stat.get(Data::get()->unitStat.getIndex("Initiative"));
}
void BattleUnitStack::startTurn() {
	for (uint16_t i = 0; i < status.size();) {
		std::vector<StatusEffect::Effect> t = status[i].getEffect();
		for (uint16_t j = 0; j < t.size(); ++j) {
			const StatusEffect::Effect& effect = t[j];
			if (Data::get()->unitStat.getVarStart() <= effect.statID && effect.statID < Data::get()->unitStat.getRangeStart() &&
				((effect.statID - Data::get()->unitStat.getVarStart()) % 2 == 0)) 
			{
				if (effect.action == '=')
					stat.set(effect.statID, effect.value);
				else if (effect.action == '+')
					stat.shift(effect.statID, effect.value);
				else if (effect.action == '-')
					stat.shift(effect.statID, -effect.value);
				else if (effect.action == '*')
					stat.mult(effect.statID, effect.value);
				else if (effect.action == '/')
					stat.mult(effect.statID, 1.0 / effect.value);
			}
		}
		status[i].shiftDuration(-1);
		if (status[i].ended())
			status.erase(status.begin() + i);
		else ++i;
	}
	recountStats();
}
void BattleUnitStack::endTurn() {
	waitInitiative = stat.get(Data::get()->unitStat.getIndex("Initiative"));
	waitEnd += Constants::get()->BATTLE_TIMER_TICK() / waitInitiative;
}



