#include "Battle.h"

#include <algorithm>
#include <iostream>

bool turnQueueSort(const BattleUnitStack* left, const BattleUnitStack* right) {
	return left->getWaitEnd() < right->getWaitEnd();
}

Battle::Battle(const std::vector<BattleArmy>& _army) :
	army(_army), battleTimer(0) 
{
	for (uint16_t i = 0; i < army.size(); ++i)
		for (uint16_t j = 0; j < army[i].getSize(); ++j)
			turnQueue.push_back(army[i].getStackPointer(j));
	std::sort(turnQueue.begin(), turnQueue.end(), turnQueueSort);
}

std::string Battle::getStatus() const {
	//REDO THIS LATER
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

void Battle::unitAction(BattleUnitStack& user, const UnitSkill& skill) {
	char actionType = skill.target;
	if (actionType == 'u') {
		user.useSkill(skill, user, std::vector<std::string>());
	}
	else if (actionType == 's') {
		uint16_t targetArmy;
		uint16_t targetNum;

		std::cout << "Write target army number: ";
		std::cin >> targetArmy;
		std::cout << "Write target number: ";
		std::cin >> targetNum;


		if (targetArmy < getArmySize() && targetNum < getArmy(targetArmy).getSize()) {
			BattleUnitStack& target = getArmy(targetArmy).getStack(targetNum);
			user.useSkill(skill, target, std::vector<std::string>());
			if (targetArmy != user.getArmy()) {
				{
					const std::vector<uint16_t>& react = user.getBase()->reaction.onAttack;
					for (uint16_t i = 0; i < react.size(); ++i) {
						user.useSkill(Data::get()->unitSkill[react[i]], target, skill.trait);
						std::cout << "Activated " << Data::get()->unitSkill[react[i]].name << " as on attack effect!\n";
					}
				}
				{
					const std::vector<uint16_t>& react = target.getBase()->reaction.onDefend;
					for (uint16_t i = 0; i < react.size(); ++i) {
						target.useSkill(Data::get()->unitSkill[react[i]], user, skill.trait);
						std::cout << "Activated " << Data::get()->unitSkill[react[i]].name << " as on defend effect!\n";
					}
				}
			}
		}
		else std::cout << "Wrong input!\n";
	}
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
				army[i].killStack(j);
			}
			else ++j;
		}
	}
	std::sort(turnQueue.begin(), turnQueue.end(), turnQueueSort);
	battleTimer = turnQueue[0]->getWaitEnd();
}


