#include "UnitTrait.h"

#include "Data.h"

#include <queue>

std::set<size_t> UnitTrait::getList() const {
	std::queue<size_t> order;
	std::set<size_t> ans;
	order.push(Data::get()->unitTrait.getIndex(name));
	while (!order.empty()) {
		size_t cur = order.front();
		order.pop();
		if (ans.find(cur) == ans.end()) {
			ans.insert(cur);
			const std::set<size_t>& t = Data::get()->unitTrait[cur].child;
			for (std::set<size_t>::iterator it = t.begin(); it != t.end(); ++it)
				order.push(*it);
		}
	}
	return ans;
}

bool UnitTrait::hasTrait(size_t trait) const {
	if (trait == Data::get()->unitTrait.getIndex(name))
		return true;
	std::queue<size_t> order;
	std::set<size_t> used;
	order.push(Data::get()->unitTrait.getIndex(name));
	while (!order.empty()) {
		size_t cur = order.front();
		order.pop();
		if (used.find(cur) == used.end()) {
			used.insert(cur);
			const std::set<size_t>& t = Data::get()->unitTrait[cur].child;
			for (std::set<size_t>::iterator it = t.begin(); it != t.end(); ++it) {
				if (*it == trait)
					return true;
				order.push(*it);
			}
		}
	}
	return false;
}

