#include "UnitStatFormula.h"

#include <stack>
#include <string>

float UnitStatFormula::count(const UnitStatList& user, const UnitStatList& target, const std::vector<std::string>& skillTrait) const {
	std::stack<float> val;
	for (uint16_t i = 0; i < expr.size(); ++i) {
		const char& c = expr[i][0];
		if ('0' <= c && c <= '9')
			val.push(std::stof(expr[i]));
		else if ('a' <= c && c <= 'z'){
			if (expr[i][1] == ':') {
				if (c == 'u')
					val.push(user.hasTrait(expr[i].substr(2)));
				else if (c == 't')
					val.push(target.hasTrait(expr[i].substr(2)));
				else if (c == 's') {
					std::string traitName = expr[i].substr(2);
					bool found = false;
					for (size_t j = 0; j < skillTrait.size() && !found; ++j)
						if (skillTrait[j] == traitName)
							found = true;
					if (found)
						val.push(1);
					else val.push(0);
				}
			}
			else if (expr[i][1] == '.') {
				if (c == 'u')
					val.push(user.get(std::stoi(expr[i].substr(2))));
				else if (c == 't')
					val.push(target.get(std::stoi(expr[i].substr(2))));
			}
		}
		else {
			float b = val.top();
			val.pop();
			float a = val.top();
			val.pop();
			if (c == '+')
				val.push(a + b);
			else if (c == '-')
				val.push(a - b);
			else if (c == '*')
				val.push(a * b);
			else if (c == '/')
				val.push(a / b);
			else if (c == '%')
				val.push((int)a % (int)b);
			else if (c == '<')
				val.push(a < b);
			else if (c == '>')
				val.push(a > b);
			else if (expr[i] == "==")
				val.push(a == b);
			else if (expr[i] == ">=")
				val.push(a >= b);
			else if (expr[i] == "<=")
				val.push(a <= b);
			else if (expr[i] == "&&")
				val.push(a && b);
			else if (expr[i] == "||")
				val.push(a || b);
		}
	}
	return val.top();
}

