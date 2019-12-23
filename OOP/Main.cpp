	
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


void loadData() {
	Constants::get()->loadFromFile("Data\\Constants.txt");
	Data::get()->unitStat.loadFromFile("Data\\UnitStat.txt");
	Data::get()->unitSkill.loadFromFile("Data\\UnitSkill.txt");
	Data::get()->unitTrait.loadFromFile("Data\\UnitTrait.txt");
	Data::get()->unit.loadFromFile("Data\\Unit.txt");
}

Battle buildBattleArmies() {
	std::string input;
	std::vector<Army> army;
	while (true) {
		system("cls");

		for (size_t i = 0; i < army.size(); ++i) {
			std::cout << "Army " << i << "\n";
			std::cout << print(army[i]) << "\n";
		}
		std::cout << std::endl;

		std::cout << "Choose one option:\n";
		std::cout << "(N)ew army:\n";
		std::cout << "(C)hange army:\n";
		std::cout << "(R)emove army:\n";
		std::cout << "(S)tart the battle:\n";
		std::cout << "(E)xit to main menu:\n";

		std::cin >> input;
		toLowerCase(input);
		removeUnderscore(input);

		if (input == "n") {
			army.push_back(Army());
			std::cout << "New army added to the list!\n";
		}
		else if (input == "c") {
			std::cout << "Write army to change: \n";
			size_t armyNumber;
			std::cin >> armyNumber;
			if (armyNumber < army.size()) {
				Army& curArmy = army[armyNumber];
				while (true) {
					system("cls");

					std::cout << "Army " << armyNumber << "\n";
					std::cout << print(curArmy) << "\n";
					std::cout << std::endl;

					std::cout << "Choose one option:\n";
					std::cout << "(N)ew unit:\n";
					std::cout << "(C)hange unit:\n";
					std::cout << "(R)emove unit:\n";
					std::cout << "(E)xit to army list:\n";

					std::cin >> input;
					toLowerCase(input);
					removeUnderscore(input);
					if (input == "n") {
						if (curArmy.isFull())
							std::cout << "Army is full!";
						else {
							bool bPrintUnits = false;
							while (true) {
								system("cls");
								std::cout << "Write unit name to add:\n";
								std::cout << "(write \"?\" to print list of all units, \"exit\" to return):\n";
								if (bPrintUnits)
									std::cout << Data::get()->unit.printNameList() << std::endl;
								
								std::getline(std::cin, input);
								removeUnderscore(input);

								if (input == "exit")
									break;
								else if (input == "?")
									bPrintUnits = true;
								else {
									std::string trueName = Data::get()->unit[input].name;
									if (trueName != input)
										std::cout << "Invalid unit name!\n";
									else {
										std::cout << "Write unit stack size:\n";
										size_t stackSize;
										std::cin >> stackSize;
										curArmy.addStack(UnitStack(input, stackSize));
										std::cout << "New army added to the list!\n";
										break;
									}
								}
								system("pause");
							}
						}
					}
					else if (input == "c") {
						std::cout << "Write unit position to change:\n";
						size_t unitNumber;
						std::cin >> unitNumber;
						if (unitNumber < curArmy.getSize()) {
							std::cout << "Write new stack size:\n";
							size_t stackSize;
							std::cin >> stackSize;
							curArmy.getStack(unitNumber).setNumber(stackSize);
							std::cout << "Stack size changed!";
						}
						else std::cout << "Invalid unit number!";
					}
					else if (input == "r") {
						std::cout << "Write unit number to remove:\n";
						size_t unitNumber;
						std::cin >> unitNumber;
						if (curArmy.deleteStack(unitNumber))
							std::cout << "Unit removed from the army!\n";
						else
							std::cout << "Invalid unit number!\n";
					}
					else if (input == "e")
						break;
					else "Invalid input!\n";
					system("pause");
				}
			}
		}
		else if (input == "r") {
			std::cout << "Write army number to remove: \n";
			size_t armyNumber;
			std::cin >> armyNumber;
			if (armyNumber < army.size()) {
				army.erase(army.begin() + armyNumber);
				std::cout << "Army removed from the list!\n";
			}
			else "Invalid army number!\n";
		}
		else if (input == "s") {
			return Battle(army);
		}
		else if (input == "e")
			break;
		else std::cout << "Invalid input!\n";
		system("pause");
	}
	return Battle(std::vector<Army>{});
}
 
void battleLoop(Battle battle) {
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
				if(!Data::get()->unitSkill[react[i]].hasTrait("SYSTEM")){
					std::cout << curUnit->getName() << " attemtps to activate " << Data::get()->unitSkill[react[i]].name << " on it's first turn!\n";
					battle.unitAction(*curUnit, Data::get()->unitSkill[react[i]]);
				} 
			}
			curUnit->endFirstTurn();
		}
		{
			const std::vector<uint16_t>& react = curUnit->getBase()->reaction.everyTurn;
			for (uint16_t i = 0; i < react.size(); ++i) {
				if (!Data::get()->unitSkill[react[i]].hasTrait("SYSTEM")) {
					std::cout << curUnit->getName() << " attempts to activate " << Data::get()->unitSkill[react[i]].name << " on it's turn!\n";
					battle.unitAction(*curUnit, Data::get()->unitSkill[react[i]]);
				}
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
				if (action < skillList.size()) {
					if (battle.unitAction(*curUnit, curUnit->getSkill(action))) {
						curUnit->endTurn();
						battle.endTurn();
						battle.startTurn();
					}
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

int main() {
	srand((uint32_t)time(NULL));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11 + 16 * 5);

	loadData();

	std::string input;
	do {
		system("cls");
		std::cout << "Choose one option:\n";
		std::cout << "(P)lay:\n";
		std::cout << "(T)est:\n";
		std::cout << "(Q)uit:\n";
		std::cin >> input;
		toLowerCase(input);

		if (input == "q" || input == "quit")
			break;	
		else if (input == "p" || input == "play") {
			Battle battle = buildBattleArmies();
			if(battle.getArmySize())
				battleLoop(battle);
		}
		else if (input == "t" || input == "test") {

			Army army1 = Army(std::vector<UnitStack>{
				UnitStack("Horned demon", 200),
				UnitStack("Hell hound", 100),
				UnitStack("Succubus", 50),
				UnitStack("Hell charger", 20),
				UnitStack("Pit fiend", 15)
			});
			Army army2 = Army(std::vector<UnitStack> {
				UnitStack("Imp", 1000),
				UnitStack("Devil", 50)
			});

			battleLoop(Battle(std::vector<Army>{army1, army2}));
			
		}
		else std::cout << "Wrong input!\n";
		system("pause");
	} while (true);

	std::cout << "Bye Bye!\n";
	system("pause");

	return 0;
}


