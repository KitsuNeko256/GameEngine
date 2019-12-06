#pragma once

#include <vector>

struct UnitStat {
	const std::string name;
	const char type;
	const int min, max, init;

	UnitStat() : name("NULL"), type(0), min(0), max(0), init(0) {}
	UnitStat(const std::string& _name, char _type, int _min, int _max, int _init) :
		name(_name), type(_type), min(_min), max(_max), init(_init) {}
};
