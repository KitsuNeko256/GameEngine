#include "DataTemplate.h"

#include <stack>
#include <string>

#include "common.h"
#include "Data.h"

#include "UnitStat.h"
#include "Unit.h"
#include "UnitStatModifier.h"
#include "UnitSkill.h"

UnitStatFormula loadUnitStatFormula(std::ifstream& fin) {
	std::string stat;
	char action;
	std::vector<std::string> expr;

	fin >> stat >> action;
	removeUnderscore(stat);

	std::string s;
	std::stack<std::string> oper;
	while (true) {
		fin >> s;
		removeUnderscore(s);
		char& c = s[0];
		if (c == '#')
			break;
		else if (c == '(')
			oper.push("(");
		else if (c == ')') {
			while (oper.top()[0] != '(') {
				expr.push_back(oper.top());
				oper.pop();
			}
			oper.pop();
		}
		else if (c == '-' || c == '+') {
			while (!oper.empty() && oper.top()[0] != '(') {
				expr.push_back(oper.top());
				oper.pop();
			}
			oper.push(s);
		}
		else if (c == '*' || c == '/') {
			while (!oper.empty() && (oper.top()[0] == '*' || oper.top()[0] == '/')) {
				expr.push_back(oper.top());
				oper.pop();
			}
			oper.push(s);
		}
		else if ('0' <= c && c <= '9')
			expr.push_back(s);
		else {
			std::string ans = "";
			ans += s[0];
			ans += s[1];
			ans += std::to_string(Data::get()->unitStat.getIndex(s.substr(2)));
			expr.push_back(ans);
		}
	}
	while (!oper.empty()) {
		expr.push_back(oper.top());
		oper.pop();
	}
	return UnitStatFormula(Data::get()->unitStat.getIndex(stat), action, expr);
}
template<>
UnitStatModifier DataTemplate<UnitStatModifier>::loadSingleInstance(std::ifstream& fin) {
	std::string name;
	uint16_t priority;
	std::vector<UnitStatFormula> effect;


	fin >> name >> priority;
	removeUnderscore(name);

	int n;
	fin >> n;
	for (int i = 0; i < n; ++i)
		effect.emplace_back(loadUnitStatFormula(fin));

	return UnitStatModifier(name, priority, effect);
}
template<>
UnitSkill DataTemplate<UnitSkill>::loadSingleInstance(std::ifstream& fin) {
	std::string name;
	std::vector<UnitSkill::Effect> effect;

	fin >> name;
	removeUnderscore(name);

	int n;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		std::string effectName;
		char target;
		uint16_t duration;
		fin >> effectName >> target >> duration;
		removeUnderscore(effectName);
		effect.push_back(UnitSkill::Effect(Data::get()->unitStatModifier.getIndex(effectName), target, duration));
	}
	return UnitSkill(name, effect);
}

template<>
UnitStat DataTemplate<UnitStat>::loadSingleInstance(std::ifstream& fin) {
	std::string name;
	float min, max;
	
	fin >> name >> min >> max;
	removeUnderscore(name);

	return UnitStat(name, min, max);
}
template<>
Unit DataTemplate<Unit>::loadSingleInstance(std::ifstream& fin) {
	std::string name;
	std::vector<float> stat;
	std::vector<uint16_t> skill;

	fin >> name;
	removeUnderscore(name);

	for (uint16_t i = 0; i < Data::get()->unitStat.getSize(); ++i) {
		float value;
		fin >> value;
		stat.emplace_back(value);
	}

	uint16_t n;
	fin >> n;
	for (uint16_t i = 0; i < n; ++i) {
		std::string skillName;
		fin >> skillName;
		removeUnderscore(skillName);
		skill.emplace_back(Data::get()->unitSkill.getIndex(skillName));
	}
		
	return Unit(name, stat, skill);
}




