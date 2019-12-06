#pragma once

#include "UnitStatModifier.h"



class UnitSkill {
public:
	const std::string name;
	const char target;
	const std::vector<std::string> trait;
	
	struct Effect {
		uint16_t ID;
		char target;
		uint16_t duration;
		Effect(uint16_t _ID, char _target, uint16_t _duration) :
			ID(_ID), target(_target), duration(_duration) {}
	};
	const std::vector<Effect> effect;
	
	UnitSkill() : name("NULL"), target(' ') {}
	UnitSkill(const std::string& _name, char _target, const std::vector<Effect>& _effect, const std::vector<std::string>& _trait) :
		name(_name), target(_target), effect(_effect), trait(_trait) {}

	bool hasTrait(std::string traitName) const {
		for (size_t i = 0; i < trait.size(); ++i)
			if (trait[i] == traitName)
				return true;
		return false;
	}
};

