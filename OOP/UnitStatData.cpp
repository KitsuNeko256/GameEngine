#include "UnitStatData.h"

#include <fstream>
#include <string>

#include "common.h"

void UnitStatData::loadFromFile(const std::string& fileName) {
	std::ifstream fin(fileName);

	for (std::map<std::string, uint16_t>::iterator it = varIndex.begin(); it != varIndex.end(); ++it)
		it->second -= varStart;
	for (std::map<std::string, uint16_t>::iterator it = rangeIndex.begin(); it != rangeIndex.end(); ++it)
		it->second -= rangeStart;

	while (!fin.eof()) {
		std::string name;
		char type;
		int min, max, init;

		fin >> name >> type >> min >> max >> init;

		removeUnderscore(name);

		if (type == 's') {
			singleIndex[name] = singleIndex.size();
			singleVal.emplace_back(UnitStat(name, type, min, max, init));
		}
		else if (type == 'v') {
			varIndex[name] = varIndex.size();
			varIndex["Max " + name] = varIndex.size();
			varVal.emplace_back(UnitStat(name, type, min, max, init));
		}
		else if (type == 'r') {
			rangeIndex[name] = rangeIndex.size();
			rangeIndex["Min " + name] = rangeIndex.size();
			rangeIndex["Max " + name] = rangeIndex.size();
			rangeVal.emplace_back(UnitStat(name, type, min, max, init));
		}
	}

	varStart = singleVal.size();
	rangeStart = varStart + varIndex.size();
	size = rangeStart + rangeIndex.size();
	valueListSize = rangeStart + (size - rangeStart) * 2 / 3;

	for (std::map<std::string, uint16_t>::iterator it = varIndex.begin(); it != varIndex.end(); ++it)
		it->second += varStart;
	for (std::map<std::string, uint16_t>::iterator it = rangeIndex.begin(); it != rangeIndex.end(); ++it)
		it->second += rangeStart;

	fin.close();
}