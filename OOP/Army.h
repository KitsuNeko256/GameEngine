#pragma once

#include <vector>

#include "Constants.h"
#include "UnitStack.h"


class Army {
private:
	std::vector<UnitStack> stack;

public:
	Army() {}
	Army(const std::vector<UnitStack>& _stack);

	int getSize() const {
		return stack.size();
	}
	bool isFull() const {
		return stack.size() == Constants::get()->ARMY_SIZE();
	}
	
	const UnitStack& getConstStack(int n) const {
		return stack[n];
	}
	UnitStack& getStack(int n) {
		return stack[n];
	}

	bool addStack(const UnitStack& _stack);
	bool deleteStack(uint16_t n);
};

