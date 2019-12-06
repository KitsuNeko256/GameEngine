#include "DataTemplate.h"

#include <sstream>
#include <string>
#include <stack>

#include "common.h"
#include "Data.h"

template<>
void DataTemplate<UnitTrait>::loadFromFile(const std::string& fileName) {
	std::ifstream fin(fileName);
	if (fin.good()) {
		size_t IDCounter = getSize();
		std::string input;
		bool end = 1;
		while (!fin.eof()) {
			fin >> input;
			removeUnderscore(input); 
			if (end) {
				index[input] = IDCounter++;
				end = 0;
			}
			else if (input == "[END]")
				end = 1;
		}
	}
	fin.close();
	fin.open(fileName);
	if (fin.good()) {
		while (!fin.eof())
			val.emplace_back(loadSingleInstance(fin));
	}
	fin.close();

}
template<>
UnitTrait DataTemplate<UnitTrait>::loadSingleInstance(std::ifstream& fin) {
	std::string name;
	std::set<size_t> child;

	fin >> name;
	removeUnderscore(name);

	std::string input;
	fin >> input;
	while (input != "[END]") {
		child.insert(getIndex(input));
		fin >> input;
	}
	
	return UnitTrait(name, child);
}

inline int operPriority(char c) {
	if (c == '|')
		return 1;
	if (c == '&')
		return 2;
	if (c == '<' || c == '>' || c == '=')
		return 3;
	if (c == '%')
		return 4;
	if (c == '-' || c == '+')
		return 5;
	if (c == '*' || c == '/')
		return 6;
	return -1;
}

std::vector<std::string> loadUnitStatExpr(std::ifstream& fin) {
	std::vector<std::string> expr;
	std::stack<std::string> oper;

	std::string str;
	getline(fin, str);
	std::istringstream ss(str);
	std::string input;

	while (ss >> input){
		removeUnderscore(input);
		char& c = input[0];
		if (c == '(')
			oper.push("(");
		else if (c == ')') {
			while (oper.top()[0] != '(') {
				expr.push_back(oper.top());
				oper.pop();
			}
			oper.pop();
		}
		else if (operPriority(c) != -1) {
			while (!oper.empty() && operPriority(c) <= operPriority(oper.top()[0])) {
				expr.push_back(oper.top());
				oper.pop();
			}
			oper.push(input);
		}
		else if ('0' <= c && c <= '9' || input[1] == ':')
			expr.push_back(input);
		else
			expr.push_back(input.substr(0, 2) + std::to_string(Data::get()->unitStat.getIndex(input.substr(2))));
	}
	
	while (!oper.empty()) {
		expr.push_back(oper.top());
		oper.pop();
	}

	return expr;
}

template<>
UnitStatModifier DataTemplate<UnitStatModifier>::loadSingleInstance(std::ifstream& fin) {
	std::string name;
	uint16_t priority;
	std::stack<UnitStatFormulaNode*> effect;
	effect.push(new UnitStatFormulaNode());

	fin >> name >> priority;
	removeUnderscore(name);

	std::string input;
	fin >> input;
	while (input != "[END]") {
		if (input == "[IF]") {
			UnitStatFormulaNode* node = new UnitStatFormulaNode();
			effect.top()->child.emplace_back(std::make_tuple(UnitStatFormula(0, 0, loadUnitStatExpr(fin)), node, nullptr));
			effect.push(node);
		}
		else if (input == "[ELSE]") {
			effect.pop();
			UnitStatFormulaNode* node = new UnitStatFormulaNode();
			std::get<2>(effect.top()->child[effect.top()->child.size() - 1]) = node;
			effect.push(node);
		}
		else if (input == "[FI]") {
			effect.pop();
		}
		else {
			char action;
			fin  >> action;
			removeUnderscore(input);
			effect.top()->value.emplace_back(Data::get()->unitStat.getIndex(input), action, loadUnitStatExpr(fin));
		}
		fin >> input;
	}
	while (effect.size() > 1) effect.pop();
	return UnitStatModifier(name, priority, effect.top());
}

template<>
UnitSkill DataTemplate<UnitSkill>::loadSingleInstance(std::ifstream& fin) {
	std::string name;
	char target;
	std::vector<UnitSkill::Effect> effect;
	std::vector<std::string> trait;

	fin >> name >> target;
	removeUnderscore(name);

	std::string input;
	fin >> input;

	while (input != "[END]") {
		if (input == "[EFFECT]")
			while (true) {
				fin >> input;
				if (input[0] == '[')
					break;
				removeUnderscore(input);
				char target;
				uint16_t duration;
				fin >> target >> duration;
				effect.push_back(UnitSkill::Effect(Data::get()->unitStatModifier.getIndex(input), target, duration));
			}
		else if (input == "[TRAIT]")
			while (true) {
				fin >> input;
				if (input[0] == '[')
					break;
				removeUnderscore(input);
				trait.push_back(input);
			}
	}

	return UnitSkill(name, target, effect, trait);
}

template<>
Unit DataTemplate<Unit>::loadSingleInstance(std::ifstream& fin) {
	std::string name;
	UnitStatList stat;
	std::vector<size_t> skill;
	UnitReaction reaction;

	fin >> name;
	removeUnderscore(name);

	const UnitStatData& data = Data::get()->unitStat;
	std::string input;

	fin >> input;
	removeUnderscore(input);
	while (input != "[END]"){
		if (input == "[STAT]")
			while (true) {
				fin >> input;
				if (input[0] == '[')
					break;
				removeUnderscore(input);
				char type = data[input].type;
				if (type == 's') {
					int val;
					fin >> val;
					stat.set(data.getIndex(input), val);
				}
				else if (type == 'v') {
					int val1, val2;
					fin >> val1 >> val2;
					stat.set(data.getIndex(input), val1);
					stat.set(data.getIndex("Max " + input), val2);
				}
				else if (type == 'r') {
					int val1, val2;
					fin >> val1 >> val2;
					stat.set(data.getIndex("Min " + input), val1);
					stat.set(data.getIndex("Max " + input), val2);
				}
			}
		else if (input == "[SKILL]")
			while (true) {
				fin >> input;
				if (input[0] == '[')
					break;
				removeUnderscore(input);
				skill.emplace_back(Data::get()->unitSkill.getIndex(input));
			}
		else if (input == "[REACTION]") {
			std::vector<uint16_t>* curVector = &reaction.firstTurn;
			while (true) {
				fin >> input;
				if (input[0] == '[')
					break;
				removeUnderscore(input);
				if (input == "{FIRST TURN}")
					curVector = &reaction.firstTurn;
				else if (input == "{EVERY TURN}")
					curVector = &reaction.everyTurn;
				else if (input == "{ON ATTACK}")
					curVector = &reaction.onAttack;
				else if (input == "{ON DEFEND}")
					curVector = &reaction.onDefend;
				else if (input == "{ON DEATH}")
					curVector = &reaction.onDeath;
				else
					curVector->emplace_back(Data::get()->unitSkill.getIndex(input));
			}
		}
		else if (input == "[TRAIT]") {
			while (true) {
				fin >> input;
				if (input[0] == '[')
					break;
				removeUnderscore(input);
				stat.addTrait(input);
			}
		}
	}
	
	stat.set(data.getIndex("Wait"), 0);

	return Unit(name, stat, skill, reaction);
}

/*
ifstream file("input.txt");
if (file.good())
{
	string str;
	file >> str;
	while (getline(file, str))
	{
		if(str == "")
			continue;
		istringstream ss(str);
		std::string input;
		while (ss >> input)
		{
			cout << input << " ";
		}
		cout << endl;
	}
}
*/