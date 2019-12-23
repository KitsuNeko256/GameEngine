#include "Battle.h"

#include <algorithm>
#include <iostream>

bool turnQueueSort(const BattleUnitStack* left, const BattleUnitStack* right) {
	return left->getWaitEnd() < right->getWaitEnd();
}

Battle::Battle(const std::vector<Army>& _army) : battleTimer(0) {
	for (uint16_t i = 0; i < _army.size(); ++i) {
		army.push_back(BattleArmy(_army[i], i, battleTimer));
		for (uint16_t j = 0; j < army[i].getSize(); ++j)
			turnQueue.push_back(army[i].getStackPointer(j));
	}
	std::sort(turnQueue.begin(), turnQueue.end(), turnQueueSort);
}
Battle::Battle(const std::vector<BattleArmy>& _army) : army(_army), battleTimer(0) {
	for (uint16_t i = 0; i < army.size(); ++i)
		for (uint16_t j = 0; j < army[i].getSize(); ++j)
			turnQueue.push_back(army[i].getStackPointer(j));
	std::sort(turnQueue.begin(), turnQueue.end(), turnQueueSort);
}

std::string Battle::getStatus() const {
	if (army[0].isDead()) {
		if (army[1].isDead())
			return "Draw";
		return "Army 1 wins";
	}
	if (army[1].isDead())
		return "Army 0 wins";
	return "Battle continues";
}
void Battle::armySurrender() {
	BattleArmy& t = army[getTurnArmy()];
	while (!t.isDead())
		t.killStack(0);
}

bool Battle::unitAction(BattleUnitStack& user, const UnitSkill& skill) {
	char actionType = skill.targeting;
	if (actionType == 'u') {
		user.useSkill(skill, user, std::vector<std::string>());
		if (skill.name == "Wait")
			std::cout << user.getName() << " waits for better moment!\n";
	}
	else if (actionType == 's') {
		uint16_t targetArmy;
		uint16_t targetNum;

		std::cout << "Write target army number: \n";
		std::cin >> targetArmy;
		std::cout << "Write target number: \n";
		std::cin >> targetNum;

		if (targetArmy < getArmySize() && targetNum < getArmy(targetArmy).getSize()) {
			BattleUnitStack& target = getArmy(targetArmy).getStack(targetNum);
			user.useSkill(skill, target, std::vector<std::string>());
			if (targetArmy != user.getArmy()) {
				{
					const std::vector<uint16_t>& react = user.getBase()->reaction.onAttack;
					for (uint16_t i = 0; i < react.size(); ++i) {
						if (!Data::get()->unitSkill[react[i]].hasTrait("SYSTEM")) {
							std::cout << user.getName() << " attempts to activate " << Data::get()->unitSkill[react[i]].name << " as on attack effect!\n";
							user.useSkill(Data::get()->unitSkill[react[i]], target, skill.trait);
						}
					}
				}
				{
					const std::vector<uint16_t>& react = target.getBase()->reaction.onDefend;
					for (uint16_t i = 0; i < react.size(); ++i) {
						if (!Data::get()->unitSkill[react[i]].hasTrait("SYSTEM")) {
							std::cout << target.getName() << " attempts to activate " << Data::get()->unitSkill[react[i]].name << " as on defend effect!\n";
							target.useSkill(Data::get()->unitSkill[react[i]], user, skill.trait);
						}
					}
				}
			}
		}
		else {
			std::cout << "Wrong input!\n";
			return false;
		}
	}
	return true;
}

void Battle::startTurn() {
	turnQueue[0]->startTurn();
}
void Battle::endTurn() {
	for (uint16_t i = 0; i < army.size(); ++i) {
		for (uint16_t j = 0; j < army[i].getSize();) {
			BattleUnitStack* t = &army[i].getStack(j);
			if (t->isDead()) {
				for(uint16_t k = 0; k < turnQueue.size(); ++k)
					if (turnQueue[k] == t) {
						turnQueue.erase(turnQueue.begin() + k);
						break;
					}
				const std::vector<uint16_t>& react = t->getBase()->reaction.onDeath;
				for (uint16_t i = 0; i < react.size(); ++i) {
					if (!Data::get()->unitSkill[react[i]].hasTrait("SYSTEM")) {
						std::cout << t->getName() << "attempts to activate " << Data::get()->unitSkill[react[i]].name << " on death!\n";
						unitAction(*t, Data::get()->unitSkill[react[i]]);
					}
				}
				army[i].killStack(j);
			}
			else ++j;
		}
	}
	std::sort(turnQueue.begin(), turnQueue.end(), turnQueueSort);
	battleTimer = turnQueue[0]->getWaitEnd();
}


