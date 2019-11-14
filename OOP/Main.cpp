	
#include <iostream>
#include <time.h>
#include <random>

#include "common.h"
#include "Constants.h"
#include "Data.h"
#include "Battle.h"
#include "Printer.h"


int main() {
	srand((uint32_t)time(NULL));
	
	Constants::get()->loadFromFile("Data\\Constants.txt");
	Data::get()->unitStat.loadFromFile("Data\\UnitStat.txt");
	Data::get()->unitStatModifier.loadFromFile("Data\\UnitStatModifier.txt");
	Data::get()->unitSkill.loadFromFile("Data\\UnitSkill.txt");
	Data::get()->unit.loadFromFile("Data\\Unit.txt");


	std::cout << "Unit Stat Modifier List:\n";
	std::cout << print(Data::get()->unitStatModifier);
	std::cout << std::endl;
	std::cout << "Unit Skill List:\n";
	std::cout << print(Data::get()->unitSkill);
	std::cout << std::endl;
	std::cout << "Unit Stat List:\n";
	std::cout << print(Data::get()->unitStat);
	std::cout << std::endl;

	system("pause");
	system("cls");

	std::cout << "Unit list:\n";
	std::cout << print(Data::get()->unit);
	std::cout << std::endl;

	system("pause");
	system("cls");

	Army army1 = Army(std::vector<UnitStack>{
		UnitStack("Horned demon", 200),
		UnitStack("Hell hound", 100),
		UnitStack("Succubus", 50),
		UnitStack("Hell charger", 20),
		UnitStack("Pit fiend", 15),
		UnitStack("Pit fiend", 15)
	});

	Army army2 = Army(std::vector<UnitStack> {
		UnitStack("Imp", 1000),
		UnitStack("Devil", 50)
	});

	std::cout << "Army 1:" << std::endl;
	std::cout << print(army1) << std::endl;
	std::cout << "Army 2:" << std::endl;
	std::cout << print(army2) << std::endl;

	system("pause");
	system("cls");

	Battle battle = Battle(std::vector<BattleArmy>{
		BattleArmy(army1), 
		BattleArmy(army2)
	});

	std::cout << print(battle) << std::endl;
	std::cout << battle.getStatus() << std::endl;

	system("pause");

	return 0;
}


