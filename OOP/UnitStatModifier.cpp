#include "UnitStatModifier.h"

UnitStatFormulaNode::~UnitStatFormulaNode() {
	for (size_t i = 0; i < child.size(); ++i){
		delete std::get<1>(child[i]);
		if(std::get<2>(child[i]) != nullptr) delete std::get<2>(child[i]);
	}
}

std::vector<const UnitStatFormula*> UnitStatFormulaNode::get(const UnitStatList& user, const UnitStatList& target, const std::vector<std::string>& skillTrait) const {
	std::vector<const UnitStatFormula*> ans;
	for (size_t i = 0; i < value.size(); ++i)
		ans.emplace_back(&value[i]);
	for (size_t i = 0; i < child.size(); ++i) {
		std::vector<const UnitStatFormula*> t;
		if (std::get<0>(child[i]).count(user, target, skillTrait))
			t = std::get<1>(child[i])->get(user, target, skillTrait);
		else if (std::get<2>(child[i]) != nullptr)
			t = std::get<2>(child[i])->get(user, target, skillTrait);
		for (size_t j = 0; j < t.size(); ++j)
			ans.emplace_back(t[j]);
	}
	return ans;
}