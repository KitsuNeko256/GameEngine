	
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
#include "Printer.h"



void testInfo(const Army& army1, const Army& army2) {

	std::cout << "Unit Stat List:\n";
	std::cout << print(Data::get()->unitStat);
	std::cout << std::endl;
	std::cout << "Unit Stat Modifier List:\n";
	std::cout << print(Data::get()->unitStatModifier);
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

	std::cout << "Army 1:" << std::endl;
	std::cout << print(army1) << std::endl;
	std::cout << "Army 2:" << std::endl;
	std::cout << print(army2) << std::endl;

	system("pause");
	system("cls");
}

int main() {
	srand((uint32_t)time(NULL));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);

	Constants::get()->loadFromFile("Data\\Constants.txt");
	Data::get()->unitStat.loadFromFile("Data\\UnitStat.txt");
	Data::get()->unitStatModifier.loadFromFile("Data\\UnitStatModifier.txt");
	Data::get()->unitSkill.loadFromFile("Data\\UnitSkill.txt");
	Data::get()->unit.loadFromFile("Data\\Unit.txt");

	std::string input;
	do {
		system("cls");
		std::cout << "Choose one option:\n";
		std::cout << "(E)ditor:\n";
		std::cout << "(T)esting:\n";
		std::cout << "(Q)uit:\n";
		std::cin >> input;
		toLowerCase(input);
		if (input == "q" || input == "quit")
			break;	
		else if (input == "e" || input == "editor") {
			std::cout << "Add editor some day\n";
//			std::cout << "Choose what to edit:\n";
//			std::cout << "1. UnitStat\n";
//			std::cout << "2. UnitStatModifier";
//			std::cout << "3. "
		}
		else if (input == "t" || input == "testing") {
			Army army1 = Army(std::vector<UnitStack>{
				UnitStack("Horned demon", 200),
					UnitStack("Hell hound", 100),
					UnitStack("Succubus", 50),
					UnitStack("Hell charger", 20),
					UnitStack("Pit fiend", 15),
					UnitStack("Pit fiend", 15)
			});

			Army army2 = Army(std::vector<UnitStack> {
				UnitStack("Imp", 100),
					UnitStack("Devil", 50)
			});

			Battle battle = Battle(std::vector<BattleArmy>{
				BattleArmy(army1, 0),
					BattleArmy(army2, 1)
			});


			while (true) {
				system("cls");
				if (battle.getStatus() != "Battle continues")
					break;

				std::cout << print(battle);

				std::cout << "Turn order:\n";
				std::vector<BattleUnitStack*> x = battle.getTurnOrder();
				for (uint16_t i = 0; i < x.size(); ++i)
					std::cout << "P" << x[i]->getArmy() << " " << x[i]->getName() << "\n";
				std::cout << std::endl;

				std::cout << "Player " << battle.getTurnArmy() << " turn.\n";
				BattleUnitStack* curUnit = battle.getTurnUnit();
				std::cout << "Current unit: " << curUnit->getName() << "\n\n";

				std::cout << "Write your action (inspect, act, wait, surrender): \n";
				std::string input;
				std::cin >> input;
				if (input == "inspect") {

					std::cout << "Choose target army number: ";
					uint16_t targetArmy;
					std::cin >> targetArmy;

					std::cout << "Choose target number: ";
					uint16_t targetNum;
					std::cin >> targetNum;

					if (targetArmy < battle.getArmySize() && targetNum < battle.getArmy(targetArmy).getSize()) {
						battle.getArmy(targetArmy).getStack(targetNum).recountStats();
						std::cout << print(battle.getArmy(targetArmy).getConstStack(targetNum)) << "\n";
					}
					else std::cout << "Wrong input!\n";

				}
				else if (input == "act") {
					std::cout << "Available actions: \n";
					const std::vector<uint16_t>& skillList = curUnit->getBase()->skill;
					for (uint16_t i = 0; i < skillList.size(); ++i)
						std::cout << i << ". " << Data::get()->unitSkill[skillList[i]].name << "\n";

					std::cout << "Choose action number: ";
					uint16_t action;
					std::cin >> action;

					std::cout << "Choose target army number: ";
					uint16_t targetArmy;
					std::cin >> targetArmy;

					std::cout << "Choose target number: ";
					uint16_t targetNum;
					std::cin >> targetNum;

					if (action < skillList.size() && targetArmy < battle.getArmySize() && targetNum < battle.getArmy(targetArmy).getSize()) {
						curUnit->recountStats();
						curUnit->useSkill(action, battle.getArmy(targetArmy).getStack(targetNum));
						curUnit->endTurn();
						battle.endTurn();
						battle.startTurn();
					}
					else std::cout << "Wrong input!\n";
				}
				else if (input == "wait") {
					curUnit->wait();
					battle.endTurn();
					battle.startTurn();
				}
				else if (input == "surrender") {
					battle.armySurrender();
				}
				else {
					std::cout << std::endl;
					std::cout << "Wrong input!\n";
				}
				system("pause");
			}
			std::cout << battle.getStatus() << "\n";
			std::cout << "Battle results: \n";
			std::cout << print(battle);
			system("pause");
		}
		else std::cout << "Wrong input!\n";
		system("pause");
	} while (true);

	std::cout << "Bye Bye!";
	system("pause");

	return 0;
}


