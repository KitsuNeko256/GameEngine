#pragma once


#include "DataTemplate.h"
#include "UnitStatModifier.h"
#include "UnitSkill.h"
#include "UnitStat.h"
#include "Unit.h"

class Data {
private:
	Data();
	Data(const Data& root) = delete;
	Data& operator=(const Data&) = delete;

public:

	DataTemplate<UnitStat> unitStat;
	DataTemplate<UnitStatModifier> unitStatModifier;
	DataTemplate<UnitSkill> unitSkill;
	DataTemplate<Unit> unit;

	static Data* instance;
	static Data* get();
};









