#pragma once

#include "Data.h"
#include "Battle.h"

#include <string>


std::string print(const UnitStat& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unitStat.getIndex(t.name)) +
		" | Name: " + t.name + " | Type: ";
	ans += t.type;
	ans += "| Min: " + std::to_string(t.min) +
		" | Max: " + std::to_string(t.max);
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

std::string print(const UnitStatFormula& t) {
	std::string ans;
	for (uint16_t i = 0; i < t.expr.size(); ++i)
		ans += " " + t.expr[i];
	return ans;
}
std::string print(const UnitStatModifier& t) {
	std::string ans = "Prioirity: " + std::to_string(t.priority) +
		" | Duration:  " + std::to_string(t.duration) + " | Target: ";
	if (t.target == 'u')
		ans += "user";
	else if (t.target == 't')
		ans += "target";
	ans += " | Stat: " + Data::get()->unitStat[t.statID].name + " ";
	ans += t.statOperator;
	return ans;
}
std::string print(const UnitSkill& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unitSkill.getIndex(t.name)) +
		" | Name: " + t.name + "  ";
	ans += t.targeting;
	return ans;
}

std::string print(const Unit& t) {
	std::string ans = "ID: " + std::to_string(Data::get()->unit.getIndex(t.name)) + 
		"| Name: " + t.name + "\n";
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
	std::string ans = t.getName() + "\n";
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
		ans += std::to_string(i) + ": " + t.getConstStack(i).getName() + " " + std::to_string(t.getConstStack(i).getNumber()) + "\n";
	return ans;
}
std::string print(Battle& t) {
	std::string ans;
	for (uint16_t i = 0; i < t.getArmySize(); ++i)
		ans += "Army " + std::to_string(i) + "\n" +
		print(t.getArmy(i)) + "\n";
	return ans;
}
std::string printTurnQueue(const Battle& t) {
	std::string ans = "Turn order:\n";
	std::vector<BattleUnitStack*> x = t.getTurnOrder();
	for (uint16_t i = 0; i < x.size(); ++i)
		ans += "P" + std::to_string(x[i]->getArmy()) + " " + x[i]->getName() + "\n";
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



//NOT UPDATED
void dataTestInfo() {

	std::cout << "Unit Stat List:\n";
	std::cout << print(Data::get()->unitStat);
	std::cout << std::endl;
	std::cout << "Unit Skill List:\n";
	std::cout << print(Data::get()->unitSkill);
	std::cout << std::endl;

	system("pause");
	system("cls");

	std::cout << "Unit list:\n";
	std::cout << print(Data::get()->unit);
	std::cout << std::endl;

	system("pause");
	system("cls");
}
