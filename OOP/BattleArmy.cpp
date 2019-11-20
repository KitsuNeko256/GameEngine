#include "BattleArmy.h"



BattleArmy::BattleArmy(const Army& army, uint16_t _armyID) : armyID(_armyID) {
	for (uint16_t i = 0; i < army.getSize(); ++i)
		stack.emplace_back(army.getConstStack(i), armyID);
}

void BattleArmy::addStack(BattleUnitStack& _stack) {
	if (isFull())
		return;
	stack.push_back(_stack);
}
void BattleArmy::killStack(uint16_t n) {
	if (n >= stack.size())
		return;
	grave.push_back(stack[n]);
	stack.erase(stack.begin() + n);
}
void BattleArmy::reviveStack(uint16_t n) {
	if (n >= grave.size() || isFull())
		return;
	stack.push_back(grave[n]);
	grave.erase(grave.begin() + n);
}
