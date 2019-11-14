#include "BattleArmy.h"



BattleArmy::BattleArmy(const Army& army) {
	for (uint16_t i = 0; i < army.getSize(); ++i)
		stack.emplace_back(army.getConstStack(i));
}

void BattleArmy::addStack(BattleUnitStack& _stack) {
	if (isFull())
		return;
	stack.push_back(_stack);
}
void BattleArmy::killStack(uint8_t n) {
	if (stack.size() <= n)
		return;
	grave.emplace_back(stack[n]);
	stack.erase(stack.begin() + n);
}
void BattleArmy::reviveStack(uint8_t n) {
	if (grave.size() <= n || isFull())
		return;
	stack.emplace_back(grave[n]);
	grave.erase(grave.begin() + n);
}
