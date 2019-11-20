#pragma once

#include <string>
#include <vector>

struct UnitStat {
	const std::string name;
	const char type;
	const int min, max;

	UnitStat() : name("NULL"), type(0), min(0), max(0) {}
	UnitStat(const std::string& _name, char _type, int _min, int _max) :
		name(_name), type(_type), min(_min), max(_max) {}
};

	
class UnitStatList {
	std::vector<int> value;
public:
	UnitStatList() {}
	UnitStatList(std::vector<int> _value) : value(_value) {}

	int get(uint16_t n) const;
	void set(uint16_t n, int val);
	void shift(uint16_t n, int val);
	void mult(uint16_t n, float val);
};


