#pragma once

#include <string>

class Constants {
private:
	Constants();
	Constants(const Constants& root) = delete;
	Constants& operator=(const Constants&) = delete;
	
	uint64_t unitStackSize;
	uint16_t armySize;
	uint16_t battleArmySize;
	uint16_t battleTimerTick;

public:

	static Constants* instance;
	static Constants* get();

	void loadFromFile(const std::string& fileName);

	uint64_t UNIT_STACK_SIZE() const {
		return unitStackSize;
	}
	uint16_t ARMY_SIZE() const {
		return armySize;
	}
	uint16_t BATTLE_ARMY_SIZE() const {
		return battleArmySize;
	}
	uint16_t BATTLE_TIMER_TICK() const{
		return battleTimerTick;
	}

};

