#pragma once

#include "UnitStat.h"

#include <map>

class UnitStatData {
private:
	std::vector<UnitStat> singleVal, varVal, rangeVal;
	std::map<std::string, uint16_t> singleIndex, varIndex, rangeIndex;

	uint16_t varStart;
	uint16_t rangeStart;
	uint16_t size;

	uint16_t valueListSize;

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
	const UnitStat operator[](const std::string& name) const {
		if (singleIndex.find(name) != singleIndex.end())
			return singleVal[singleIndex.at(name)];
		if (varIndex.find(name) != varIndex.end())
			return varVal[(varIndex.at(name) - varStart) / 2];
		if (rangeIndex.find(name) != rangeIndex.end())
			return rangeVal[(rangeIndex.at(name) - rangeStart) / 3];
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
	uint16_t getSize() const {
		return size;
	}
	uint16_t getValueListSize() const {
		return valueListSize;
	}

	bool isFirstVar(uint16_t index) const {
		return varStart <= index && index < rangeStart && ((index - rangeStart) % 2 == 0);
	}
	bool isFirstRange(uint16_t index) const {
		return rangeStart <= index && ((index - rangeStart) % 3 == 0);
	}

	void loadFromFile(const std::string& fileName);
};
