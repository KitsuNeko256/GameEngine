#pragma once

#include <string>
#include <vector>

class UnitStatList {
	std::vector<int> value;
	std::vector<std::string> trait;

public:
	UnitStatList();
	UnitStatList(const std::vector<int>& _value, const std::vector<std::string>& _trait) : value(_value), trait(_trait) {}

	int get(size_t index) const;
	void set(size_t index, int val);
	void shift(size_t index, int val);
	void mult(size_t index, float val);
	void change(size_t index, float val, char action);

	bool hasTrait(const std::string& name) const;
	void addTrait(const std::string& name);
};


