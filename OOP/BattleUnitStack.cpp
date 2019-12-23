#include "BattleUnitStack.h"

#include <algorithm>
#include <iostream>

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
	for (uint16_t i = 0; i < status.size(); ++i)
		if (Data::get()->unitStat.isFirstVar(status[i].getStatID()))
			stat.change(status[i].getStatID(), status[i].getValue(), status[i].getStatOperator());
}
void BattleUnitStack::recountStaticStats() {
	resetStats();
	for (uint16_t i = 0; i < status.size(); ++i)
		if (!Data::get()->unitStat.isFirstVar(status[i].getStatID()))
			stat.change(status[i].getStatID(), status[i].getValue(), status[i].getStatOperator());
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


	{
		const std::vector<uint16_t>& react = getBase()->reaction.everyInteraction;
		for (uint16_t i = 0; i < react.size(); ++i) {
			useSkill(Data::get()->unitSkill[react[i]], *this, std::vector<std::string>());
//			std::cout << "Activated " << Data::get()->unitSkill[react[i]].name << " as every interaction effect!\n";
		}
	}
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

	if (effect.ended())
		if (Data::get()->unitStat.isFirstVar(effect.getStatID()))
			stat.change(effect.getStatID(), effect.getValue(), effect.getStatOperator());

	recountStaticStats();
}
void BattleUnitStack::useSkill(const UnitSkill& skill, BattleUnitStack& target, const std::vector<std::string>& reactionTrait) {
	const std::vector<const UnitStatModifier*> effect = skill.effect->get(stat, target.stat, reactionTrait);
	if (effect.size() == 0) {
		if (!skill.hasTrait("SYSTEM"))
			std::cout << "It fails!\n";
		return;
	}

	for (uint16_t i = 0; i < effect.size(); ++i) {
		std::string output = " " + Data::get()->unitStat[effect[i]->statID].name + " got ";
		switch (effect[i]->statOperator) {
		case '+':
			output += "increased by ";
			break;
		case '-':
			output += "decreased by ";
			break;
		case '*':
			output += "multiplied by ";
			break;
		case '/':
			output += "divided by ";
			break;
		case '=':
			output += "set to ";
			break;
		}

		if(effect[i]->statOperator == '*' || effect[i]->statOperator == '/')
			output += std::to_string(effect[i]->formula.count(stat, target.stat, reactionTrait)) + "!";
		else
			output += std::to_string((int)effect[i]->formula.count(stat, target.stat, reactionTrait)) + "!";
		if (effect[i]->target == 'u') {
			addStatusEffect(StatusEffect(skill.name, *effect[i], effect[i]->formula.count(stat, target.stat, reactionTrait)));
			output = getName() + output; 
		}
		else if (effect[i]->target == 't') {
			target.addStatusEffect(StatusEffect(skill.name, *effect[i], effect[i]->formula.count(stat, target.stat, reactionTrait)));
			output = target.getName() + output;
		}
		if (effect[i]->printable)
			std::cout << output << "\n";
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

	if (!skill.hasTrait("SYSTEM")) {
		{
			const std::vector<uint16_t>& react = getBase()->reaction.everyInteraction;
			for (uint16_t i = 0; i < react.size(); ++i) {
				useSkill(Data::get()->unitSkill[react[i]], *this, skill.trait);
//				std::cout << "Activated " << Data::get()->unitSkill[react[i]].name << " as every interaction effect!\n";
			}
		}
		if(&target != this){
			const std::vector<uint16_t>& react = target.getBase()->reaction.everyInteraction;
			for (uint16_t i = 0; i < react.size(); ++i) {
				target.useSkill(Data::get()->unitSkill[react[i]], target, skill.trait);
//				std::cout << "Activated " << Data::get()->unitSkill[react[i]].name << " as every interaction effect!\n";
			}
		}
	}
}



