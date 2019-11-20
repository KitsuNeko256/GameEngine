#pragma once

#include "Constants.h"
#include "BattleUnitStack.h"
#include "Army.h"




class BattleArmy {
private:
	uint16_t armyID;

	std::vector<BattleUnitStack> stack;
	std::vector<BattleUnitStack> grave;

public:
	BattleArmy(const Army& army, uint16_t _armyID);

	int getSize() const{
		return stack.size();
	}
	bool isFull() const{
		return stack.size() == Constants::get()->BATTLE_ARMY_SIZE();
	}
	bool isDead() const {
		return stack.size() == 0;
	}
	const BattleUnitStack& getConstStack(int n) const{
		return stack[n];
	}
	BattleUnitStack& getStack(int n) {
		return stack[n];
	}

	void addStack(BattleUnitStack& _stack);
	void killStack(uint16_t n);
	void reviveStack(uint16_t n);
};