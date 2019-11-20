#include "common.h"
#include "Data.h"

#include <iostream>

void UnitStatData::loadFromFile(const std::string& fileName) {
	std::ifstream fin(fileName);

	while (!fin.eof()) {
		std::string name;
		char type;
		float min, max;

		fin >> name >> type >> min >> max;

		removeUnderscore(name);

		if (type == 's') {
			singleIndex[name] = singleIndex.size();
			singleVal.emplace_back(UnitStat(name, type, min, max));
		}
		else if (type == 'v') {
			varIndex[name] = varIndex.size();
			varIndex["MAX " + name] = varIndex.size();
			varVal.emplace_back(UnitStat(name, type, min, max));
		}
		else if (type == 'r') {
			rangeIndex[name] = rangeIndex.size();
			rangeIndex["MIN " + name] = rangeIndex.size();
			rangeIndex["MAX " + name] = rangeIndex.size();
			rangeVal.emplace_back(UnitStat(name, type, min, max));
		}
	}

	varStart = singleVal.size();
	rangeStart = varStart + varIndex.size();
	size = rangeStart + rangeIndex.size(); 

	for (std::map<std::string, uint16_t>::iterator it = varIndex.begin(); it != varIndex.end(); ++it)
		it->second += varStart;
	for (std::map<std::string, uint16_t>::iterator it = rangeIndex.begin(); it != rangeIndex.end(); ++it)
		it->second += rangeStart;

	fin.close();
}


Data::Data() {}
Data* Data::instance;
Data* Data::get() {
	if (instance == nullptr) instance = new Data();
	return instance;
}
