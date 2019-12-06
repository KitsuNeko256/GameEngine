#include "BattleArmy.h"



BattleArmy::BattleArmy(const Army& army, size_t _armyID, const uint64_t& _battleTimer) :
	armyID(_armyID), battleTimer(_battleTimer)
{
	for (uint16_t i = 0; i < army.getSize(); ++i)
		stack.emplace_back(new BattleUnitStack(army.getConstStack(i), armyID, battleTimer));
}

void BattleArmy::addStack(BattleUnitStack& _stack) {
	if (isFull())
		return;
	stack.push_back(&_stack);
}
void BattleArmy::killStack(size_t n) {
	if (n < stack.size()) {
		grave.push_back(stack[n]);
		stack.erase(stack.begin() + n);
	}
}
void BattleArmy::reviveStack(size_t n) {
	if (n < grave.size() && !isFull()) {
		stack.push_back(grave[n]);
		grave.erase(grave.begin() + n);
	}
}

