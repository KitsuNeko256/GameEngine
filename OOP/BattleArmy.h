#pragma once

#include "Constants.h"
#include "BattleUnitStack.h"
#include "Army.h"


class BattleArmy {
private:
	size_t armyID;

	const uint64_t& battleTimer;

	std::vector<BattleUnitStack*> stack;
	std::vector<BattleUnitStack*> grave;

public:
	BattleArmy(const Army& army, size_t _armyID, const uint64_t& _battleTimer);

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
		return *stack[n];
	}
	BattleUnitStack& getStack(int n) {
		return *stack[n];
	}
	BattleUnitStack* getStackPointer(int n) {
		return stack[n];
	}

	void addStack(BattleUnitStack& _stack);
	void killStack(size_t n);
	void reviveStack(size_t n);
};