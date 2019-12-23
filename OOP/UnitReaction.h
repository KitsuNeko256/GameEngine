#pragma once

#include "UnitSkill.h"

struct UnitReaction {
	std::vector<uint16_t> everyInteraction;
	std::vector<uint16_t> firstTurn;
	std::vector<uint16_t> everyTurn;
	std::vector<uint16_t> onAttack;
	std::vector<uint16_t> onDefend;
	std::vector<uint16_t> onDeath;

	UnitReaction() {}
	UnitReaction(const std::vector<uint16_t>& _everyInteraction,
		const std::vector<uint16_t>& _firstTurn,
		const std::vector<uint16_t>& _everyTurn,
		const std::vector<uint16_t>& _onAttack, 
		const std::vector<uint16_t>& _onDefend, 
		const std::vector<uint16_t>& _onDeath) :
		everyInteraction(_everyInteraction), firstTurn(_firstTurn), 
		everyTurn(_everyTurn), onAttack(_onAttack), onDefend(_onDefend), onDeath(_onDeath) {}
};