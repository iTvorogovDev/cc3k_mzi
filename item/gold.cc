#include "gold.h"
#include "../dungeon/cell.h"
#include <iostream>
Gold::Gold(std::string type, std::shared_ptr<Actor> d):goldType{ type },
dragon{ d }{
       // c = nullptr;
	if (type == "S") {
		hoard = false;
		value = 1;
	}
	else if (type == "N")
	{
		hoard = false;
		value = 2;
	}
	else if (type == "DH")
	{
//cout << "dragon hoard spawned" << endl;
		hoard = true;
		value = 6;
	}
	else {
		hoard = false;
		value = 4;
	}
}

std::string Gold::getType() {
	return goldType;
};

bool Gold::isHoard() {
	return hoard;
};

int Gold::getValue() {
	return value;
}

std::shared_ptr<Actor> Gold::getDragon() {
	return dragon;
}

void Gold::setDragon(std::shared_ptr<Actor> d) {
	dragon = d;
}

/*void Gold::setCell(std::shared_ptr<Cell> c) {
	c->setType('G');
	c->setItem(this);
}*/
