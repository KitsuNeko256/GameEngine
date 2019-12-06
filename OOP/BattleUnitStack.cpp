#include "BattleUnitStack.h"

#include <algorithm>

#include "Constants.h"

BattleUnitStack::BattleUnitStack(const UnitStack& t, size_t _army, const uint64_t& _battleTimer) :
	base(&(Data::get()->unit[t.getType()])), army(_army), stat(base->stat),
	battleTimer(_battleTimer), firstTurn(true),
	waitInitiative(stat.get(Data::get()->unitStat.getIndex("Initiative"))),
	waitEnd(battleTimer + Constants::get()->BATTLE_TIMER_TICK() / waitInitiative)
{
	stat.set(Data::get()->unitStat.getIndex("Number"), t.getNumber());
	stat.set(Data::get()->unitStat.getIndex("Max Number"), t.getNumber());
}

void BattleUnitStack::updateHealth() {
	const UnitStatData& data = Data::get()->unitStat;
	size_t HealthID = data.getIndex("Health");
	size_t NumberID = data.getIndex("Number");
	int maxHealth = stat.get(data.getIndex("Max Health"));
	int maxNumber = stat.get(data.getIndex("Max Number"));
	int Health = stat.get(HealthID);
	int Number = stat.get(NumberID);

	if (Health > maxHealth) {
		if (Health / maxHealth > maxNumber - Number) {
			stat.set(NumberID, maxNumber);
			stat.set(HealthID, maxHealth);
		}
		else {
			stat.shift(NumberID, Health / maxHealth);
			stat.set(HealthID, Health % maxHealth);
		}
	}
	else if (Health < 0) {
		Health *= -1;
		if (Health / maxHealth >= Number - 1) {
			stat.set(NumberID, 0);
		}
		else {
			stat.shift(NumberID, -1 - Health / maxHealth);
			stat.set(HealthID, maxHealth - (Health % maxHealth));
		}
	}
}


void BattleUnitStack::resetStats() {
	uint16_t NumberID = Data::get()->unitStat.getIndex("Number");
	for (uint16_t i = 0; i < Data::get()->unitStat.getVarStart(); ++i)
		stat.set(i, base->stat.get(i));
	for (uint16_t i = Data::get()->unitStat.getVarStart(); i < Data::get()->unitStat.getRangeStart(); i += 2)
		if (i != NumberID)
			stat.set(i + 1, base->stat.get(i + 1));
	for (uint16_t i = Data::get()->unitStat.getRangeStart(); i < Data::get()->unitStat.getSize(); i += 3) {
		stat.set(i + 1, base->stat.get(i + 1));
		stat.set(i + 2, base->stat.get(i + 2));
	}
}
void BattleUnitStack::recountVarStats() {
	for (uint16_t i = 0; i < status.size(); ++i) {
		std::vector<StatusEffect::Effect> effect = status[i].getEffect();
		for (uint16_t j = 0; j < effect.size(); ++j) {
			if (Data::get()->unitStat.isFirstVar(effect[j].statID))
				stat.change(effect[j].statID, effect[j].value, effect[j].action);
		}
	}
	stat.set(Data::get()->unitStat.getIndex("Retaliate Count"), stat.get(Data::get()->unitStat.getIndex("Max Retaliate Count")));
	updateHealth();
}
void BattleUnitStack::recountStaticStats() {
	resetStats();

	for (uint16_t i = 0; i < status.size(); ++i) {
		std::vector<StatusEffect::Effect> effect = status[i].getEffect();
		for (uint16_t j = 0; j < effect.size(); ++j) {
			if (!Data::get()->unitStat.isFirstVar(effect[j].statID))
				stat.change(effect[j].statID, effect[j].value, effect[j].action);
		}
	}
}

void BattleUnitStack::updateTimer() {
	recountStaticStats();
	waitEnd = (waitEnd - battleTimer) * waitInitiative + ((float)stat.get(Data::get()->unitStat.getIndex("Wait")) / 10000.0 * Constants::get()->BATTLE_TIMER_TICK());
	waitInitiative = stat.get(Data::get()->unitStat.getIndex("Initiative"));
	waitEnd = (waitEnd / waitInitiative) + battleTimer;
}
void BattleUnitStack::startTurn() {
	recountVarStats();
	for (uint16_t i = 0; i < status.size();) {
		status[i].shiftDuration(-1);
		if (status[i].ended())
			status.erase(status.begin() + i);
		else ++i;
	}
	recountStaticStats();
}
void BattleUnitStack::endTurn() {
	recountStaticStats();

	waitInitiative = stat.get(Data::get()->unitStat.getIndex("Initiative"));
	waitEnd += (stat.get((float)stat.get(Data::get()->unitStat.getIndex("Wait")) / 10000.0 * Constants::get()->BATTLE_TIMER_TICK()) + 
		Constants::get()->BATTLE_TIMER_TICK()) / waitInitiative;
}

void BattleUnitStack::addStatusEffect(StatusEffect&& effect) {
	std::vector<StatusEffect>::iterator it = std::lower_bound(status.begin(), status.end(), effect);
	if (it != status.end())
		status.insert(++it, effect);
	else status.emplace_back(effect);

	if (effect.ended()) {
		const std::vector<StatusEffect::Effect>& t = effect.getEffect();
		for (uint16_t i = 0; i < t.size(); ++i)
			if (Data::get()->unitStat.isFirstVar(t[i].statID))
				stat.change(t[i].statID, t[i].value, t[i].action);
	}

	updateHealth();
	recountStaticStats();
}
void BattleUnitStack::useSkill(const UnitSkill& skill, BattleUnitStack& target, const std::vector<std::string>& reactionTrait) {
	for (uint16_t i = 0; i < skill.effect.size(); ++i) {
		const UnitStatModifier modifier = Data::get()->unitStatModifier[skill.effect[i].ID];
		const std::vector<const UnitStatFormula*> formula = modifier.effect->get(stat, target.stat, reactionTrait);
		std::vector<StatusEffect::Effect> effect;
		for (uint16_t j = 0; j < formula.size(); ++j)
			effect.emplace_back(formula[j]->statIndex, formula[j]->action, formula[j]->count(stat, target.stat, reactionTrait));
		if (effect.size() > 0) {
			if (skill.effect[i].target == 'u')
				addStatusEffect(StatusEffect(modifier.name, modifier.priority, skill.effect[i].duration, effect));
			if (skill.effect[i].target == 't')
				target.addStatusEffect(StatusEffect(modifier.name, modifier.priority, skill.effect[i].duration, effect));
		}
	}
	updateTimer();
	for (uint16_t i = 0; i < status.size();) {
		if (status[i].ended())
			status.erase(status.begin() + i);
		else ++i;
	}
	recountStaticStats();

	if (&target != this) {
		target.updateTimer();
		for (uint16_t i = 0; i < target.status.size();) {
			if (target.status[i].ended())
				target.status.erase(target.status.begin() + i);
			else ++i;
		}
		target.recountStaticStats();
	}
}



