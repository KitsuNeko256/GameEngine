#pragma once

#include <string>

struct UnitStat {
	const std::string name;
	const float min, max;

	UnitStat() : name("NULL"), min(0), max(0) {}
	UnitStat(const std::string _name, float _min, float _max) :
		name(_name), min(_min), max(_max) {}
};


