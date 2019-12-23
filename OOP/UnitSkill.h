#pragma once

#include "UnitStatModifier.h"

struct UnitSkill {
	const std::string name;
	const char targeting;
	const std::vector<std::string> trait;
	
	const UnitStatModifierNode* effect;
	
	UnitSkill() : name("NULL"), targeting(' ') {}
	UnitSkill(const std::string& _name, char _targeting, const std::vector<std::string>& _trait, const UnitStatModifierNode* _effect) :
		name(_name), targeting(_targeting), trait(_trait), effect(_effect) {}

	bool hasTrait(std::string traitName) const {
		for (size_t i = 0; i < trait.size(); ++i)
			if (trait[i] == traitName)
				return true;
		return false;
	}
};

