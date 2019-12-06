#pragma once

#include <vector>
#include <map>

#include "UnitStatList.h"

struct UnitStatFormula {
	const size_t statIndex;
	const char action;
	const std::vector<std::string> expr;

	UnitStatFormula() : statIndex(0), action (0) {};
	UnitStatFormula(uint16_t _statIndex, char _action, const std::vector<std::string>& _expr) :
		statIndex(_statIndex), action(_action), expr(_expr) {}

	float count(const UnitStatList& user, const UnitStatList& target, const std::vector<std::string>& skillTrait) const;
};

	