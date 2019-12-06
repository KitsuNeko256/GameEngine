#pragma once

#include <string>

#include "UnitStack.h"
#include "UnitSkill.h"
#include "UnitStatusEffect.h"
#include "Data.h"

class BattleUnitStack {
private:
	const Unit* base;
	size_t army;

	UnitStatList stat;
	std::vector<StatusEffect> status;

	const uint64_t& battleTimer;
	int waitInitiative;
	uint64_t waitEnd;

	bool firstTurn;

public:
//	BattleUnitStack() {}
	BattleUnitStack(const UnitStack& t, size_t _army, const uint64_t& _battleTimer);

/////////////
// GETTERS //
/////////////

	const Unit* getBase() const {
		return base;
	}
	std::string getName() const {
		return base->name;
	}
	bool hasTrait(std::string traitName) const {
		return base->hasTrait(traitName);
	}
	
	size_t getArmy() const {
		return army;
	}
	uint64_t getWaitEnd() const {
		return waitEnd;
	}
	
	bool isFirstTurn() const {
		return firstTurn;
	}
	int getNumber() const {
		return stat.get(Data::get()->unitStat.getIndex("Number"));
	}
	bool isDead() const {
		return getNumber() == 0;
	}

	const UnitStatList& getStatList() const {
		return stat;
	}
	const UnitSkill& getSkill(size_t number) const {
		return Data::get()->unitSkill[base->skill[number]];
	}
	const std::vector<StatusEffect>& getStatus() const {
		return status;
	}

///////////////
// FUNCTIONS //
///////////////

	void endFirstTurn() {
		firstTurn = false;
	}

	void updateHealth();

	void resetStats();
	void recountVarStats(); // Health, Mana etc.
	void recountStaticStats();

	void updateTimer();
	void startTurn();
	void endTurn();

	void addStatusEffect(StatusEffect&& effect);
	void useSkill(const UnitSkill& skill, BattleUnitStack& target, const std::vector<std::string>& reactionTrait);
	
};






