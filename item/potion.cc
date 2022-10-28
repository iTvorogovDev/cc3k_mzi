#include "potion.h"
#include "../dungeon/cell.h"
#include <string>

Potion::Potion(std::string type, int hpMod, int atkMod, int defMod): 
potionType{type}, atkMod{atkMod}, defMod{defMod}, hpMod{hpMod}{}

std::string Potion::getPotionType() {
	return potionType;
}

int Potion::getAtkMod() {
	return atkMod;
}

int Potion::getDefMod() {
	return defMod;
}

int Potion::getHPMod() {
	return hpMod;
}
/*
void Potion::setCell(Cell &c) {
	c.setType('P');
	c.setItem(this);
}*/
