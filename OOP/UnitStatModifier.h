#pragma once

#include "UnitStatFormula.h"

struct UnitStatFormulaNode {
	std::vector<UnitStatFormula> value;
	std::vector<std::tuple<UnitStatFormula, UnitStatFormulaNode*, UnitStatFormulaNode*> >child;

	~UnitStatFormulaNode();

	std::vector<const UnitStatFormula*> get(const UnitStatList& user, const UnitStatList& target, const std::vector<std::string>& skillTrait) const;
};

struct UnitStatModifier {
public:
	const std::string name;
	const uint16_t priority;
	const UnitStatFormulaNode* effect;
	
	UnitStatModifier() :
		name("NULL"), priority(0), effect(new UnitStatFormulaNode()) {}
	UnitStatModifier(const std::string& _name, const uint16_t _priority, const UnitStatFormulaNode* _effect) :
		name(_name), priority(_priority), effect(_effect) {}
};
