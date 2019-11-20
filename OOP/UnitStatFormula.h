#pragma once

#include <vector>
#include <map>

#include "UnitStat.h"

struct UnitStatFormula {
	const uint16_t stat;
	const char action;
	const std::vector<std::string> expr;

	UnitStatFormula() : stat(0), action ('+') {};
	UnitStatFormula(uint16_t tStat, char _action, std::vector<std::string> _expr) :
		stat(tStat), action(_action), expr(_expr) {}

	float count(const UnitStatList& user, const UnitStatList& target) const;
};

	