#pragma once

#include "BattleArmy.h"

class Battle {
private:
	std::vector<BattleArmy> army;
	std::vector<BattleUnitStack*> unitOrder;
	uint64_t battleTimer;

public:
	Battle(const std::vector<BattleArmy>& _army);

	size_t getArmySize() const {
		return army.size();
	}
	BattleArmy& getArmy(uint16_t number) {
		return army[number];
	}

	uint16_t getTurnArmy() {
		return unitOrder[0]->getArmy();
	}
	BattleUnitStack* getTurnUnit() {
		return unitOrder[0];
	}
	std::vector <BattleUnitStack*> getTurnOrder() {
		return unitOrder;
	}
	std::string getStatus() const;

	void unitAction(std::string& action);
	void armySurrender();

	void startTurn();
	void endTurn();
};


