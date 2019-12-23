#pragma once

#include <vector>
#include <map>

#include "UnitStatList.h"

struct UnitStatFormula {
	const std::vector<std::string> expr;

	UnitStatFormula(){};
	UnitStatFormula(const std::vector<std::string>& _expr) : expr(_expr) {}

	float count(const UnitStatList& user, const UnitStatList& target, const std::vector<std::string>& skillTrait) const;
};
