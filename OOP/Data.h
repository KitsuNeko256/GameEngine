#pragma once


#include "DataTemplate.h"
#include "UnitStatData.h"
#include "UnitTrait.h"
#include "UnitSkill.h"
#include "Unit.h"


class Data {
private:
	Data();
	Data(const Data& root) = delete;
	Data& operator=(const Data&) = delete;

public:

	UnitStatData unitStat;
	DataTemplate<UnitTrait> unitTrait;
	DataTemplate<UnitSkill> unitSkill;
	DataTemplate<Unit> unit;

	static Data* instance;
	static Data* get();
};



