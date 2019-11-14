#pragma once

#include "UnitStatFormula.h"


struct UnitStatModifier {
public:
	const std::string name;
	const uint16_t priority;
	const std::vector<UnitStatFormula> effect;
	
	UnitStatModifier() :
		name("NULL"), priority(0) {}
	UnitStatModifier(const std::string& _name, const uint16_t _priority, const std::vector<UnitStatFormula>& _effect) :
		name(_name), priority(_priority), effect(_effect) {}
};
