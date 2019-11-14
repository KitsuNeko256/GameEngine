#pragma once

#include "UnitStatModifier.h"

class UnitSkill {
private:

public:
	const std::string name;

	struct Effect {
		uint16_t ID;
		char target;
		uint16_t duration;
		Effect(uint16_t _ID, char _target, uint16_t _duration) :
			ID(_ID), target(_target), duration(_duration) {}
	};

	const std::vector<Effect> effect;
	
	UnitSkill() : name("NULL") {}

	UnitSkill(const std::string& _name, const std::vector<Effect>& _effect) :
		name(_name), effect(_effect) {}

};

