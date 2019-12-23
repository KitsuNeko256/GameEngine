#include "UnitStatModifier.h"

UnitStatModifierNode::~UnitStatModifierNode() {
	for (size_t i = 0; i < child.size(); ++i){
		delete std::get<1>(child[i]);
		if(std::get<2>(child[i]) != nullptr) delete std::get<2>(child[i]);
	}
}

std::vector<const UnitStatModifier*> UnitStatModifierNode::get(const UnitStatList& user, const UnitStatList& target, const std::vector<std::string>& skillTrait) const {
	std::vector<const UnitStatModifier*> ans;
	size_t valueI = 0;
	size_t childI = 0;
	for (size_t i = 0; i < order.size(); ++i) {
		if(order[i] == 'v')
			ans.emplace_back(&value[valueI++]);
		else if (order[i] == 'c') {
			std::vector<const UnitStatModifier*> t;
			if (std::get<0>(child[childI]).count(user, target, skillTrait))
				t = std::get<1>(child[childI])->get(user, target, skillTrait);
			else if (std::get<2>(child[childI]) != nullptr)
				t = std::get<2>(child[childI])->get(user, target, skillTrait);
			for (size_t j = 0; j < t.size(); ++j)
				ans.emplace_back(t[j]);
			++childI;
		}
	}
	return ans;
}


