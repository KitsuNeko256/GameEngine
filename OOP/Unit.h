#pragma once

#include <string>
#include <vector>

#include "UnitSkill.h"

struct Unit {
	const std::string name;
	const std::vector<float> stat;
	const std::vector<uint16_t> skill;

	Unit() : name("NULL"), stat() {}
	Unit(const std::string& _name, const std::vector<float>& tStat, const std::vector<uint16_t>& _skill) :
		name(_name), stat(tStat), skill(_skill) {}
};


//kkeeeeeekk
//asdadasdas