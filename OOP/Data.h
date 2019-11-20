#pragma once


#include "DataTemplate.h"
#include "UnitStatModifier.h"
#include "UnitSkill.h"
#include "UnitStat.h"
#include "Unit.h"

class UnitStatData{
private:
	std::vector<UnitStat> singleVal, varVal, rangeVal;
	std::map<std::string, uint16_t> singleIndex, varIndex, rangeIndex;
	uint16_t varStart;
	uint16_t rangeStart;
	uint16_t size;

public:
	const UnitStat operator[](uint16_t index) const {
		if (index < varStart)
			return singleVal[index];
		if (index < rangeStart)
			return varVal[(index - varStart) / 2];
		if (index < size)
			return rangeVal[(index - rangeStart) / 3];
		return UnitStat();
	}
	const UnitStat& operator[](const std::string& name) const {
		if (singleIndex.find(name) != singleIndex.end())
			return singleVal[singleIndex.at(name)];
		if (varIndex.find(name) != varIndex.end())
			return varVal[varIndex.at(name)];
		if (rangeIndex.find(name) != rangeIndex.end())
			return rangeVal[rangeIndex.at(name)];
		return UnitStat();
	}

	uint16_t getIndex(const std::string& name) const {
		if (singleIndex.find(name) != singleIndex.end())
			return singleIndex.at(name);
		if (varIndex.find(name) != varIndex.end())
			return varIndex.at(name);
		if (rangeIndex.find(name) != rangeIndex.end())
			return rangeIndex.at(name);
		return size;
	}
	uint16_t getVarStart() const {
		return varStart;
	}
	uint16_t getRangeStart() const {
		return rangeStart;
	}
	size_t getSize() const {
		return size;
	}
	void loadFromFile(const std::string& fileName);
};





class Data {
private:
	Data();
	Data(const Data& root) = delete;
	Data& operator=(const Data&) = delete;

public:

	UnitStatData unitStat;
	DataTemplate<UnitStatModifier> unitStatModifier;
	DataTemplate<UnitSkill> unitSkill;
	DataTemplate<Unit> unit;

	static Data* instance;
	static Data* get();
};









