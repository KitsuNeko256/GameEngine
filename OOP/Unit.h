#pragma once

#include <string>
#include <vector>

#include "UnitReaction.h"

struct Unit {
	const std::string name;
	const UnitStatList stat;
	const std::vector<size_t> skill;
	const UnitReaction reaction;

	Unit() : name("NULL"), stat() {}
	Unit(const std::string& _name, const UnitStatList& tStat, const std::vector<size_t>& _skill, const UnitReaction& _reaction) :
		name(_name), stat(tStat), skill(_skill), reaction(_reaction) {}

	bool hasTrait(const std::string& name) const {
		return stat.hasTrait(name);
	}
};

