#pragma once

#include <string>

#include "Unit.h"

class UnitStack {
private:
	size_t type;
	uint32_t number;

public:
	UnitStack();
	UnitStack(const std::string& name, uint32_t _number);
	UnitStack(size_t _unit, uint32_t _number);

	size_t getType() const {
		return type;
	}
	uint32_t getNumber() const {
		return number;
	}

	void setType(const std::string& name);
	void setType(size_t _type);
	void setNumber(uint32_t _number);
	void shiftNumber(uint32_t _number);
}; 
