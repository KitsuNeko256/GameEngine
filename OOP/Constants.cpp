#include "Constants.h"

#include <string>
#include <fstream>

Constants::Constants() {}
Constants* Constants::instance;
Constants* Constants::get() {
	if (instance == nullptr) instance = new Constants();
	return instance;
}

void Constants::loadFromFile(const std::string& fileName) {
	std::ifstream fin(fileName);
	while (!fin.eof()) {
		std::string name;
		fin >> name;
		if (name == "UNIT_STACK_SIZE")
			fin >> unitStackSize;
		else if (name == "ARMY_SIZE")
			fin >> armySize;
		else if (name == "BATTLE_ARMY_SIZE")
			fin >> battleArmySize;
		else if (name == "BATTLE_TIMER_TICK")
			fin >> battleTimerTick;
	}
	fin.close();
}