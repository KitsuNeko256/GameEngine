#pragma once

#include "Data.h"
#include "Battle.h"

#include <string>



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
	for (uint16_t i = 0; i < t.effect.size(); ++i)
		ans += print(t.effect[i]) + "\n";
	return ans;
}
std::string print(const UnitSkill& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unitSkill.getIndex(t.name)) +
		" Name: " + t.name + "\n";
	for (uint16_t i = 0; i < t.effect.size(); ++i) {
		ans += "ID: " + std::to_string(t.effect[i].ID) +
			" Target: " + t.effect[i].target +
			" Duration: " + std::to_string((int)t.effect[i].duration) + "\n";
	}
	return ans;
}

std::string print(const UnitStat& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unitStat.getIndex(t.name)) +
		" Name: " + t.name + " Type: ";
	ans += t.type;
	ans += " Min: " + std::to_string(t.min) +
		" Max: " + std::to_string(t.max);
	return ans;
}
std::string print(const UnitStatList& t) {
	const UnitStatData& data = Data::get()->unitStat;
	std::string ans = "Stats: \n";
	for (uint16_t i = 0; i < data.getVarStart(); ++i)
		ans += data[i].name + " " + std::to_string(t.get(i)) + "\n";
	for (uint16_t i = data.getVarStart(); i < data.getRangeStart(); i += 2)
		ans += data[i].name + " " + std::to_string(t.get(i)) + "/" + std::to_string(t.get(i + 1)) + "\n";
	for (uint16_t i = data.getRangeStart(); i < data.getSize(); i += 3)
		ans += data[i].name + " " + std::to_string(t.get(i + 1)) + "-" + std::to_string(t.get(i + 2)) + "\n";
	return ans;
}

std::string print(const Unit& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unit.getIndex(t.name)) + 
		" Name: " + t.name + "\n";
	ans += print(t.stat);
	ans += "Skills: ";
	for (uint16_t i = 0; i < t.skill.size(); ++i)
		ans += " " + Data::get()->unitSkill[t.skill[i]].name + ";";
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
	ans += print(t.getStatList());
	ans += "Status:\n";
	const std::vector<StatusEffect>& status = t.getStatus();
	for (uint16_t i = 0; i < status.size(); ++i)
		ans += status[i].getName() + " Duration: " + std::to_string(status[i].getDuration());
	return ans;
}
std::string print(const BattleArmy& t) {
	std::string ans;
	for (uint16_t i = 0; i < t.getSize(); ++i)
		ans += std::to_string(i) + ": " + t.getConstStack(i).getName() + " " + std::to_string(t.getConstStack(i).getSize()) + "\n";
	return ans;
}
std::string print(Battle& t) {
	std::string ans;
	for (uint16_t i = 0; i < t.getArmySize(); ++i)
		ans += "Army " + std::to_string(i) + "\n" +
		print(t.getArmy(i)) + "\n";
	return ans;
}

template<class T>
std::string print(const DataTemplate<T>& t) {
	std::string ans;
	for (uint16_t i = 0; i < t.getSize(); ++i)
		ans += print(t[i]) + "\n";
	return ans;
}

std::string print(const UnitStatData& t) {
	std::string ans;
	for (uint16_t i = 0; i < t.getSize(); ++i)
		ans += print(t[i]) + "\n";
	return ans;
}

