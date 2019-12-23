#pragma once

#include "UnitStatFormula.h"

struct UnitStatModifier {
	const char target;
	const uint16_t statID;
	const char statOperator;

	const bool printable;

	const uint16_t priority;
	const uint16_t duration;
	const UnitStatFormula formula;

	UnitStatModifier() :
		target(0), statID(0), statOperator(0), priority(0), duration(0), printable(0) {}
	UnitStatModifier(char _target, uint16_t _statID, char _statOperator, bool _printable, uint16_t _priority, uint16_t _duration, const UnitStatFormula& _formula) :
		target(_target), statID(_statID), statOperator(_statOperator), printable(_printable), priority(_priority), duration(_duration), formula(_formula) {}
};

struct UnitStatModifierNode {
	std::vector<UnitStatModifier> value;
	std::vector<std::tuple<UnitStatFormula, UnitStatModifierNode*, UnitStatModifierNode*> >child;
	std::vector<char> order;

	~UnitStatModifierNode();

	std::vector<const UnitStatModifier*> get(const UnitStatList& user, const UnitStatList& target, const std::vector<std::string>& skillTrait) const;
};





