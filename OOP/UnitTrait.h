#pragma once

#include <string>
#include <set>

class UnitTrait {
	std::set<size_t> child;
public:
	const std::string name;

	UnitTrait(const std::string& _name, const std::set<size_t>& _child) :
		name(_name), child(_child) {}
	std::set<size_t> getList() const;
	bool hasTrait(size_t trait) const;
};
