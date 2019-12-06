#include "UnitStatList.h"

#include "common.h"
#include "Data.h"

UnitStatList::UnitStatList() {
	UnitStatData& data = Data::get()->unitStat;
	value.resize(data.getValueListSize());
	for (size_t i = 0; i < data.getSize(); ++i)
		set(i, data[i].init);
}

inline void limitStat(size_t index, int& val) {
	val = toRange(Data::get()->unitStat[index].min, val, Data::get()->unitStat[index].max);
}
size_t countIndex(size_t index) {
	uint16_t rangeStart = Data::get()->unitStat.getRangeStart();
	if (index >= rangeStart)
		return (index - rangeStart) * 2 / 3 + rangeStart;
	return index;
}

int UnitStatList::get(size_t index) const {
	if (Data::get()->unitStat.isFirstRange(index)) {
		index = countIndex(index);
		return (rand() % (value[index + 1] - value[index] + 1)) + value[index];
	}
	return value[countIndex(index)];
}

void UnitStatList::set(size_t index, int val) {
	if (Data::get()->unitStat.isFirstVar(index)) {
		value[index] = val;
		return;
	}
	limitStat(index, val);
	if (Data::get()->unitStat.isFirstRange(index)){
		index = countIndex(index);
		value[index] = val;
		value[index + 1] = val;
	}
	else value[countIndex(index)] = val;
}
void UnitStatList::shift(size_t index, int val) {
	if (Data::get()->unitStat.isFirstVar(index)) {
		value[index] += val;
		return;
	}
	uint16_t outIndex = index;
	if (Data::get()->unitStat.isFirstRange(index)) {
		index = countIndex(index);
		limitStat(outIndex, value[index] += val);
		limitStat(outIndex, value[index + 1] += val);
	}
	else limitStat(outIndex, value[countIndex(index)] += val);
}
void UnitStatList::mult(size_t index, float val) {
	if (Data::get()->unitStat.isFirstVar(index)) {
		value[index] *= val;
		return;
	}
	uint16_t outIndex = index;
	if (Data::get()->unitStat.isFirstRange(index)) {
		index = countIndex(index);
		limitStat(outIndex, value[index] *= val);
		limitStat(outIndex, value[index + 1] *= val);
	}
	else limitStat(outIndex, value[countIndex(index)] *= val);
}
void UnitStatList::change(size_t index, float val, char action) {
	if (action == '=')
		set(index, val);
	else if (action == '+')
		shift(index, val);
	else if (action == '-')
		shift(index, -val);
	else if (action == '*')
		mult(index, val);
	else if (action == '/')
		mult(index, 1 / val);
}

bool UnitStatList::hasTrait(const std::string& name) const {
	for (size_t i = 0; i < trait.size(); ++i)
		if (trait[i] == name)
			return true;
	return false;
}
void UnitStatList::addTrait(const std::string& name) {
	trait.push_back(name);
}


