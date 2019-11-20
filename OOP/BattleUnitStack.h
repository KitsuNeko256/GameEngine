#pragma once

#include <string>

#include "UnitStack.h"
#include "UnitSkill.h"
#include "StatusEffect.h"

class BattleUnitStack {
private:
	const Unit* base;

	UnitStatList stat;

	int maxSize;
	int size;

	std::vector<StatusEffect> status;

	uint16_t army;

	uint32_t waitEnd;
	uint16_t waitInitiative;

public:
	BattleUnitStack() {}
	BattleUnitStack(const UnitStack& t, uint16_t _army, uint64_t timer = 0);

	std::string getName() const {
		return base->name;
	}
	const Unit* getBase() const {
		return base;
	}
	uint16_t getArmy() const {
		return army;
	}
	uint64_t getWaitEnd() const {
		return waitEnd;
	}
	int getSize() const {
		return size;
	}
	int getMaxSize() const {
		return maxSize;
	}
	const UnitStatList& getStatList() const{
		return stat;
	}
	int getStat(uint16_t n) const {
		return stat.get(n);
	}
	const std::vector<StatusEffect>& getStatus() const {
		return status;
	}

	bool isDead() const {
		return size == 0;
	}

	void wait();
	void updateTimer(uint64_t timer);
	void updateHP();
	void recountStats();
	void startTurn();
	void endTurn();

	void applyStatusEffect(StatusEffect&& effect);
	void useSkill(uint16_t skillNumber, BattleUnitStack& target);
	
};






