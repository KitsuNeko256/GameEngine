#pragma once

#include "BattleArmy.h"

class Battle {
private:
	std::vector <BattleArmy> army;
	std::vector <BattleUnitStack*> unitOrder;
	uint64_t battleTimer;

public:
	Battle(const std::vector<BattleArmy>& _army) :
		army(_army) {};

	size_t getArmySize() const {
		return army.size();
	}
	const BattleArmy& getArmy(uint8_t number) const {
		return army[number];
	}

	BattleUnitStack* getTurn() {
		return unitOrder[0];
	}
	std::vector <BattleUnitStack*> getTurnOrder() {
		return unitOrder;
	}
	std::string getStatus() const;

	
	
	void unitAction(std::string& action);

};


