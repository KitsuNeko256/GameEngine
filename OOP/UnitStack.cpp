
#include "UnitStack.h"

#include "common.h"
#include "Constants.h"
#include "Data.h"

UnitStack::UnitStack() : type(0), number(0) {};
UnitStack::UnitStack(const std::string& name, uint32_t _number) :
	type(Data::get()->unit.getIndex(name)), 
	number(toRange(0, _number, Constants::get()->UNIT_STACK_SIZE())) {}
UnitStack::UnitStack(uint16_t _unit, uint32_t _number) :
	type(_unit), number(_number) { }

void UnitStack::setType(const std::string& name) {
	uint16_t t = Data::get()->unit.getIndex(name);
}
void UnitStack::setType(uint16_t _type) {
	if(_type < Data::get()->unit.getSize())
		type = _type;
	else type = 0;
}
void UnitStack::setNumber(uint32_t _number) {
	number = toRange(0, _number, Constants::get()->UNIT_STACK_SIZE());
}
void UnitStack::shiftNumber(uint32_t _number) {
	number = toRange(0, (number+_number), Constants::get()->UNIT_STACK_SIZE());
}




