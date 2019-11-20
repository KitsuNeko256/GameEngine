#include "Battle.h"

#include <algorithm>

bool unitOrderSort(const BattleUnitStack* left, const BattleUnitStack* right) {
	return left->getWaitEnd() < right->getWaitEnd();
}

Battle::Battle(const std::vector<BattleArmy>& _army) :
	army(_army), battleTimer(0) {
	for (uint16_t i = 0; i < army.size(); ++i)
		for (uint16_t j = 0; j < army[i].getSize(); ++j)
			unitOrder.push_back(&(army[i].getStack(j)));
	std::sort(unitOrder.begin(), unitOrder.end(), unitOrderSort);
}


void Battle::unitAction(std::string& action) {
//	if (action == "attack")
//		getCurrentUnit()->hit(target);
}

void Battle::armySurrender() {
	BattleArmy& t = army[getTurnArmy()];
	while (!t.isDead())
		t.killStack(0);
}

std::string Battle::getStatus() const{
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


void Battle::startTurn() {
	unitOrder[0]->startTurn();
}
void Battle::endTurn() {
	for (uint16_t i = 0; i < army.size(); ++i) {
		for (uint16_t j = 0; j < army[i].getSize();) {
			BattleUnitStack* t = &army[i].getStack(j);
			if (t->isDead()) {
				for(uint16_t k = 0; k < unitOrder.size(); ++k)
					if (unitOrder[k] == t) {
						unitOrder.erase(unitOrder.begin() + k);
						break;
					}
				army[i].killStack(j);
			}
			else ++j;
		}
	}
	unitOrder.clear();
	for (uint16_t i = 0; i < army.size(); ++i)
		for (uint16_t j = 0; j < army[i].getSize(); ++j) {
			army[i].getStack(j).updateTimer(battleTimer);
			unitOrder.push_back(&(army[i].getStack(j)));
		}
	std::sort(unitOrder.begin(), unitOrder.end(), unitOrderSort);
	battleTimer = unitOrder[0]->getWaitEnd();
}