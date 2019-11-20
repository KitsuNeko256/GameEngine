#pragma once

#include "UnitStatModifier.h"


class StatusEffect {
public:
	struct Effect {
		uint16_t statID;
		char action;
		float value;

		Effect(uint16_t _statID, char _action, float _value) :
			statID(_statID), action(_action), value(_value) {}
		Effect& operator=(const Effect& t) = default;
	};
private:
	std::string name;
	uint16_t priority;
	uint16_t duration;

	std::vector<Effect> effect;

public:
	StatusEffect(const std::string& _name, const uint16_t _priority, uint16_t _duration, const std::vector<Effect>& _effect) :
		name(_name), priority(_priority), duration(_duration), effect(_effect) { }	

	std::string getName() const {
		return name;
	}
	uint16_t getPriority() const {
		return priority;
	}
	std::vector<Effect> getEffect() const {
		return effect;
	}

	bool operator<(const StatusEffect& right) const {
		return priority < right.priority;
	}

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


