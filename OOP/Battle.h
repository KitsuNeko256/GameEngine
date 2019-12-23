#pragma once

#include "BattleArmy.h"

class Battle {
private:
	std::vector<BattleArmy> army;
	std::vector<BattleUnitStack*> turnQueue;
	uint64_t battleTimer;

public:
	Battle(const std::vector<Army>& _army);
	Battle(const std::vector<BattleArmy>& _army);

	size_t getArmySize() const {
		return army.size();
	}
	BattleArmy& getArmy(uint16_t number) {
		return army[number];
	}

	size_t getTurnArmy() {
		return turnQueue[0]->getArmy();
	}
	BattleUnitStack* getTurnUnit() {
		return turnQueue[0];
	}
	const std::vector <BattleUnitStack*>& getTurnOrder() const {
		return turnQueue;
	}
	std::string getStatus() const;
	const uint64_t& getTimer() const {
		return battleTimer;
	}

	bool unitAction(BattleUnitStack& user, const UnitSkill& skill);
	void armySurrender();

	void startTurn();
	void endTurn();
};


