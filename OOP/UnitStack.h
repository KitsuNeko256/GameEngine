#pragma once

#include <string>

#include "Unit.h"

class UnitStack {
private:
	uint16_t type;
	uint32_t number;

public:
	UnitStack();
	UnitStack(const std::string& name, uint32_t _number);
	UnitStack(uint16_t _unit, uint32_t _number);

	uint16_t getType() const {
		return type;
	}
	uint32_t getNumber() const {
		return number;
	}

	void setType(const std::string& name);
	void setType(uint16_t _type);
	void setNumber(uint32_t _number);
	void shiftNumber(uint32_t _number);
}; 
