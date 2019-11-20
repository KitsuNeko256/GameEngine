#include "UnitStat.h"

#include "Data.h"

int countIndex(uint16_t& n) {
	uint16_t rangeStart = Data::get()->unitStat.getRangeStart();
	if (n >= rangeStart)
		return (n - rangeStart) * 2 / 3 + rangeStart;
	return n;
}
bool isRangeFirst(uint16_t n) {
	return n >= Data::get()->unitStat.getRangeStart() && ((n - Data::get()->unitStat.getRangeStart()) % 3 == 0);
}

int UnitStatList::get(uint16_t n) const {
	if (isRangeFirst(n)) {
		n = countIndex(n);
		return (rand() % (value[n + 1] - value[n] + 1)) + value[n];
	}
	return value[countIndex(n)];
}
void UnitStatList::set(uint16_t n, int val) {
	if (isRangeFirst(n)){
		n = countIndex(n);
		value[n] = val;
		value[n + 1] = val;
		return;
	}
	value[countIndex(n)] = val;
}
void UnitStatList::shift(uint16_t n, int val) {
	if (isRangeFirst(n)) {
		n = countIndex(n); 
		value[n] += val;
		value[n + 1] += val;
		return;
	}
	value[countIndex(n)] += val;
}
void UnitStatList::mult(uint16_t n, float val) {
	if (isRangeFirst(n)) {
		n = countIndex(n);
		value[n] *= val;
		value[n + 1] *= val;
		return;
	}
	value[countIndex(n)] *= val;
}
