#pragma once

#include <string>

#include "UnitStack.h"
#include "UnitSkill.h"
#include "StatusEffect.h"

class BattleUnitStack {
private:
	const Unit* base;
	
	std::vector<float> stat;

	int maxSize;
	int curSize;

	std::multimap<uint16_t, StatusEffect> status;

	uint32_t waitStart;
	uint32_t waitEnd;

public:
	BattleUnitStack() {}
	BattleUnitStack(const UnitStack& t);

	const std::vector<float>& getStatVector() const {
		return stat;
	}
	float getStat(uint8_t number) const {
		return stat[number];
	}
		
	std::string getName() const {
		return base->name;
	}
	int getSize() const {
		return curSize;
	}
	int getMaxSize() const {
		return maxSize;
	}

	
	void setStat(uint8_t number, float value);
	void shiftStat(uint8_t number, float value);
	void recountStats();

	void applyStatusEffect(StatusEffect&& effect);
	void useSkill(uint8_t skillNumber, BattleUnitStack& target);
	
};






