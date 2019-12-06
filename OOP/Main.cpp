	
#include <iostream>
#include <time.h>
#include <random>

#include <windows.h>
#undef min
#undef max

#include "common.h"
#include "Constants.h"
#include "Data.h"
#include "Battle.h"
#include "DebugPrinter.h"
 

int main() {
	srand((uint32_t)time(NULL));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hConsole, 15);
	SetConsoleTextAttribute(hConsole, 11 + 16 * 5);

	Constants::get()->loadFromFile("Data\\Constants.txt");
	Data::get()->unitStat.loadFromFile("Data\\UnitStat.txt");
	Data::get()->unitStatModifier.loadFromFile(std::string("Data\\UnitStatModifier.txt"));
	Data::get()->unitSkill.loadFromFile("Data\\UnitSkill.txt");
	Data::get()->unitTrait.loadFromFile("Data\\UnitTrait.txt");
	Data::get()->unit.loadFromFile("Data\\Unit.txt");

	std::string input;
	do {
		system("cls");
		std::cout << "Choose one option:\n";
		std::cout << "(T)esting:\n";
		std::cout << "(Q)uit:\n";
		std::cin >> input;
		toLowerCase(input);
		if (input == "q" || input == "quit")
			break;	
		else if (input == "t" || input == "testing") {
			
			Army army1 = Army(std::vector<UnitStack>{
				UnitStack("Horned demon", 200),
				UnitStack("Hell hound", 100),
				UnitStack("Succubus", 50),
				UnitStack("Hell charger", 20),
				UnitStack("Pit fiend", 15)
			});
			Army army2 = Army(std::vector<UnitStack> {
				UnitStack("Imp", 100),
				UnitStack("Devil", 50)
			});
			Battle battle = Battle(std::vector<BattleArmy>{
				BattleArmy(army1, 0, battle.getTimer()),
				BattleArmy(army2, 1, battle.getTimer())
			});

			while (true) {
				system("cls");
				if (battle.getStatus() != "Battle continues")
					break;

				std::cout << print(battle);
				std::cout << printTurnQueue(battle);
				std::cout << std::endl;

				BattleUnitStack* curUnit = battle.getTurnUnit();
				std::cout << "Player " << curUnit->getArmy() << " turn.\n";
				std::cout << "Current unit: " << curUnit->getName() << "\n\n";

				if (curUnit->isFirstTurn()) {
					const std::vector<uint16_t>& react = curUnit->getBase()->reaction.firstTurn;
					for (uint16_t i = 0; i < react.size(); ++i) {
						battle.unitAction(*curUnit, Data::get()->unitSkill[react[i]]);
						std::cout << "Activated " << Data::get()->unitSkill[react[i]].name << " on it's first turn!\n";
					}
					curUnit->endFirstTurn();
				}
				{
					const std::vector<uint16_t>& react = curUnit->getBase()->reaction.everyTurn;
					for (uint16_t i = 0; i < react.size(); ++i) {
						battle.unitAction(*curUnit, Data::get()->unitSkill[react[i]]);
						std::cout << "Activated " << Data::get()->unitSkill[react[i]].name << " on it's turn!\n";
					}
				}

				std::cout << "Write your action: \n";
				const std::vector<size_t>& skillList = curUnit->getBase()->skill;
				for (size_t i = 0; i < skillList.size(); ++i)
					std::cout << i << ". " << Data::get()->unitSkill[skillList[i]].name << "\n";
				std::cout << "i. Inspect\n";
				std::cout << "s. Surrender\n";
				std::string input;
				std::cin >> input;
				toLowerCase(input);

				if (input == "i" || input == "inspect") {
					std::cout << "Choose target army number: ";
					size_t targetArmy;
					std::cin >> targetArmy;

					std::cout << "Choose target number: ";
					size_t targetNum;
					std::cin >> targetNum;

					if (targetArmy < battle.getArmySize() && targetNum < battle.getArmy(targetArmy).getSize())
						std::cout << print(battle.getArmy(targetArmy).getConstStack(targetNum)) << "\n";
					else std::cout << "Wrong input!\n";
				}
				else if (input == "s" || input == "surrender") {
					battle.armySurrender();
				}
 				else {
					bool numFlag = true;
					for (size_t i = 0; i < input.size(); ++i)
						if (input[i] < '0' || '9' < input[i]) {
							numFlag = false;
							break;
						}
					if (numFlag) {
						size_t action = stoi(input);
						if (action < skillList.size()){
							battle.unitAction(*curUnit, curUnit->getSkill(action));
							curUnit->endTurn();
							battle.endTurn();
							battle.startTurn();
						}
						else std::cout << "Wrong input!\n";
					}

					else std::cout << "Wrong input!\n";	
				}
				system("pause");
			}
			std::cout << battle.getStatus() << "\n";
			std::cout << "Battle results: \n";
			std::cout << print(battle);
		}
		else std::cout << "Wrong input!\n";
		system("pause");
	} while (true);

	std::cout << "Bye Bye!";
	system("pause");

	return 0;
}


