#pragma once

#include "Data.h"
#include "Battle.h"

#include <string>

template<class T>
std::string print(DataTemplate<T> t) {
	std::string ans;
	for (uint16_t i = 0; i < t.getSize(); ++i)
		ans += print(t[i]) + "\n";
	return ans;
}


std::string print(const UnitStatFormula& t) {
	std::string ans = std::to_string(t.stat) + " ";
	ans += t.action;
	ans += " :";
	for (uint16_t i = 0; i < t.expr.size(); ++i)
		ans += " " + t.expr[i];
	return ans;
}
std::string print(const UnitStatModifier& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unitStatModifier.getIndex(t.name)) +
		" Name: " + t.name + " Prioirity: " + std::to_string(t.priority) + "\n";
	for (uint8_t i = 0; i < t.effect.size(); ++i)
		ans += print(t.effect[i]) + "\n";
	return ans;
}
std::string print(const UnitSkill& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unitSkill.getIndex(t.name)) +
		" Name: " + t.name + "\n";
	for (uint8_t i = 0; i < t.effect.size(); ++i) {
		ans += "ID: " + std::to_string(t.effect[i].ID) +
			" Target: " + t.effect[i].target +
			" Duration: " + std::to_string((int)t.effect[i].duration) + "\n";
	}
	return ans;
}

std::string print(const UnitStat& t) {
	return "ID: " + std::to_string(Data::get()->unitStat.getIndex(t.name)) +
		" Name: " + t.name +
		" Min: " + std::to_string(t.min) +
		" Max: " + std::to_string(t.max);
}
std::string print(const Unit& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unit.getIndex(t.name)) + 
		" Name: " + t.name + "\n";
	for (uint16_t i = 0; i < Data::get()->unitStat.getSize(); ++i)
		ans += " " + Data::get()->unitStat[i].name + ": " + std::to_string(t.stat[i]) + "\n";
	ans += "Skills: ";
	for (uint8_t i = 0; i < t.skill.size(); ++i)
		ans += " " + Data::get()->unitSkill[t.skill[i]].name;
	return ans + "\n";
}

std::string print(const UnitStack& t) {
	return Data::get()->unit[t.getType()].name + " " + std::to_string(t.getNumber());
}
std::string print(const Army& t) {
	std::string ans;
	for (uint16_t i = 0; i < t.getSize(); ++i)
		ans += print(t.getConstStack(i)) + "\n";
	return ans;
}


std::string print(const BattleUnitStack& t) {
	std::string ans = t.getName() +
		" Size: " + std::to_string(t.getSize()) + 
		"/" + std::to_string(t.getMaxSize()) + "\n";
	for (uint8_t i = 0; i < t.getStatVector().size(); ++i)
		ans += " " + Data::get()->unitStat[i].name + " " + std::to_string(t.getStat(i)) + "\n";
	return ans;
}
std::string print(const BattleArmy& t) {
	std::string ans;
	for (uint16_t i = 0; i < t.getSize(); ++i)
		ans += print(t.getConstStack(i)) + "\n";
	return ans;
}
std::string print(const Battle& t) {
	std::string ans;
	for (uint8_t i = 0; i < t.getArmySize(); ++i)
		ans += "Army " + std::to_string(i) + "\n" +
		print(t.getArmy(i)) + "\n";
	return ans;
}
