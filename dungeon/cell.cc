#include "../display/observer.h"
#include "../actor/actor.h"
#include "cell.h"

using namespace std;

Cell::Cell():pos{0, 0}{
  type = '.';
  baseType = '.';
  i = nullptr;
  a = nullptr;
}

Cell::Cell(char type,int row, int col) :type{ type }, 
  baseType{ type },	
  pos{ row, col } {
	i = nullptr;
	a = nullptr;
};

Cell::~Cell() {
};

void Cell::setbaseType(char t){
  baseType = t;
}

shared_ptr<Item> Cell::getItem(){
  return i;
}

Coordinate Cell::getCoord() {
	return pos;
}

char Cell::getType() {
	return type;
};

bool Cell::isPlayerMovable() {
	return (type == '#' || type == '+' || type == '.');
};

bool Cell::isNPCMovable() {
	return (type == '.');
};

void Cell::actorDead(std::string actorRace) {
	type = '.';
}

void Cell::itemTaken(std::string itemtype) {
	type = '.';
}

void Cell::setPos(int newx, int newy) {
	pos.setX(newx);
	pos.setY(newy);
}

void Cell::setChamberBelong(int newChamberNum) {
	pos.setChamber_Belong(newChamberNum);
}

void Cell::setItem(std::shared_ptr<Item> item) {
        if(item){
		i = item;
 	} else {
        	i = nullptr;
        }
};

void Cell::setType(char a_type) {
	type = a_type;
}

void Cell::setActor(std::shared_ptr<Actor> anactor){
 	if (anactor) {
          a = anactor;
        } else {
          a = nullptr;
        }
}

std::shared_ptr<Actor> Cell::getActor(){
  return a;
}

void Cell::reset(){
  type = baseType;
  a = nullptr;
  i = nullptr;
}
