
#include "common.h"
#include "Army.h"

Army::Army(const std::vector<UnitStack>& _stack) : stack(_stack) {
	if (stack.size() > Constants::get()->ARMY_SIZE())
		stack.resize(Constants::get()->ARMY_SIZE());
}

bool Army::addStack(const UnitStack& _stack) {
	if (isFull())
		return false;
	stack.emplace_back(_stack);
	return true;
}
bool Army::deleteStack(uint16_t n) {
	if (stack.size() <= n)
		return false;
	stack.erase(stack.begin() + n);
	return true;
}
