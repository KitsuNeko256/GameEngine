#pragma once

#include "UnitStatModifier.h"


class StatusEffect {
private:
	uint16_t duration;

public:
	const std::string name;
	const uint16_t priority;

	struct Effect{
		uint16_t statID;
		char action;
		float value;

		Effect(uint16_t _statID, char _action, float _value) :
			statID(_statID), action(_action), value(_value) {}
	};
	const std::vector<Effect> effect;

	StatusEffect(const std::string& _name, const uint16_t _priority, uint16_t _duration, const std::vector<Effect>& _effect) :
		name(_name), priority(_priority), duration(_duration), effect(_effect) { }

	bool ended() const {
		return !duration;
	}
	uint16_t getDuration() const {
		return duration;
	}
	void setDuration(uint16_t _duration) {
		duration = _duration;
	}
	void shiftDuration(uint16_t shift) {
		duration += shift;
	}
};





