#include "UnitStatFormula.h"

#include <stack>
#include <string>

float UnitStatFormula::count(const std::vector<float>& user, const std::vector<float>& target) const {
	std::stack<float> val;
	for (uint16_t i = 0; i < expr.size(); ++i) {
		const char& c = expr[i][0];
		if ('0' <= c && c <= '9')
			val.push(std::stof(expr[i]));
		else if ('a' <= c && c <= 'z'){
			if (c == 'u')
				val.push(user[std::stoi(expr[i].substr(2))]);
			else if (c == 't')
				val.push(target[std::stoi(expr[i].substr(2))]);
		}
		else {
			float b = val.top();
			val.pop();
			float a = val.top();
			val.pop();
			if (c == '+')
				val.push(a + b);
			if (c == '-')
				val.push(a - b);
			if (c == '*')
				val.push(a * b);
			if (c == '/')
				val.push(a / b);
		}
	}
	return val.top();
}
