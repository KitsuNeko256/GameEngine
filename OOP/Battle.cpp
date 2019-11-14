#include "Battle.h"



void Battle::unitAction(std::string& action) {
//	if (action == "attack")
//		getCurrentUnit()->hit(target);
}

std::string Battle::getStatus() const{
//REDO THIS LATER
	if (army[0].isDead()) {
		if (army[1].isDead())
			return "Draw";
		return "Army 2 wins";
	}
	if (army[1].isDead())
		return "Army 1 wins";
	return "War never ends";
}


