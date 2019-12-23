#pragma once

#include "UnitStatModifier.h"

class StatusEffect {
	std::string name;
	uint16_t priority;
	uint16_t duration;

	uint16_t statID;
	char statOperator;
	float value;

public:
	StatusEffect(const std::string& _name, uint16_t _priority, uint16_t _duration, uint16_t _statID, char _statOperator, float _value) :
		name(_name), priority(_priority), duration(_duration), statID(_statID), statOperator(_statOperator), value(_value) { }
	StatusEffect(const std::string& _name, const UnitStatModifier& modifier, float _value) :
		name(_name), priority(modifier.priority), duration(modifier.duration), statID(modifier.statID), statOperator(modifier.statOperator), value(_value) {}

	std::string getName() const {
		return name;
	}
	uint16_t getPriority() const {
		return priority;
	}
	uint16_t getDuration() const {
		return duration;
	}
	uint16_t getStatID() const {
		return statID;
	}
	char getStatOperator() const {
		return statOperator;
	}
	float getValue() const {
		return value;
	}

	bool ended() const {
		return !duration;
	}
	void setDuration(uint16_t _duration) {
		duration = _duration;
	}
	void shiftDuration(uint16_t shift) {
		duration += shift;
	}

	bool operator<(const StatusEffect& right) const {
		return priority < right.priority;
	}
};



/*

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

	uint16_t getDuration() const {
		return duration;
	}
	bool ended() const {
		return !duration;
	}
	void setDuration(uint16_t _duration) {
		duration = _duration;
	}
	void shiftDuration(uint16_t shift) {
		duration += shift;
	}

	bool operator<(const StatusEffect& right) const {
		return priority < right.priority;
	}
};


*/