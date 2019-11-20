#pragma once

#include <string>
#include <vector>

#include "UnitSkill.h"

struct Unit {
	const std::string name;
	const UnitStatList stat;
	const std::vector<uint16_t> skill;

	Unit() : name("NULL"), stat() {}
	Unit(const std::string& _name, const UnitStatList& tStat, const std::vector<uint16_t>& _skill) :
		name(_name), stat(tStat), skill(_skill) {}
};

