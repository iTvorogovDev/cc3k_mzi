#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

#include "chamber.h"
#include "cell.h"
#include "../item/gold.h"
#include "../item/potion.h"
#include "../actor/actor.h"
#include "../race/race.h"

class Merchant;
using namespace std;

// constructor
Chamber::Chamber(int chamberNum) :chamberNum{ chamberNum }, cellNum{ 0 }{ 
};

Chamber::~Chamber(){
  room.clear();
}


// private function to get a cell with corresponding coordinate
// from 'this' chamber
std::shared_ptr<Cell> Chamber::getCell(Coordinate coord) {
  for (auto &c : room) {
    if (c->getCoord().getX() == coord.getX() &&
        c->getCoord().getY() == coord.getY()) {
	return c;
	
    }
  }

  return nullptr;
}

// manually set a random cell to a given type
void Chamber::setCell(char cellType) {
  int i;
  while (true) {
    i = rand()%(cellNum);
    std::shared_ptr<Cell> tmp = room[i];
    if (tmp->getType() == '.') {
      tmp->setType(cellType);
      break;
    };
  };
}

vector < shared_ptr<Cell> > Chamber::getRoom(){
  return room;
}

// this function will be used in floor.cc to set a cell
// pointer to the correspoinding chamber
void Chamber::pushCell(std::shared_ptr<Cell> c) {
  bool isCin = false;
  for (auto &acell : room) {
    Coordinate tmpCooord = acell->getCoord();
    Coordinate cCoord = c->getCoord();
    if (tmpCooord.getX() == cCoord.getX() &&
        tmpCooord.getY() == cCoord.getY()) {
      isCin = true;
      c->setChamberBelong(chamberNum);
    }
  };

  if (!isCin) {
    c->setChamberBelong(chamberNum);
    room.emplace_back(c);
  };
  cellNum++;
}

Coordinate Chamber::setCelltoDragon(Coordinate c, shared_ptr<Actor> dragonptr) {
//This function would be called only 
//when a dragon is needed to be spawned.
//
// c is the place where the dragon hoard is spawned.

  char dragonChar = 'D';
  std::shared_ptr<Cell> tmp = nullptr;
  int i = rand()%(8);
  bool EAempty = true, NEempty = true, 
       NOempty = true, NWempty = true, 
       SEempty = true, SOempty = true, 
       SWempty = true, WEempty = true;

while (EAempty || NEempty || NOempty || NWempty ||
       SEempty || SOempty || SWempty || WEempty){
// check if all places around the cell is occupied, if is, then the
// dragon's health is manually set to 0
  if (i == 0 && EAempty) {
    tmp = getCell(c.coordEA());
    if(tmp != nullptr && tmp->getType() == '.'){ break; }
    else { EAempty = false; };
  }
  else if (i == 1 && NEempty) {
    tmp = getCell(c.coordNE());
    if(tmp != nullptr && tmp->getType() == '.'){ break; }
    else { NEempty = false; };
  }
  else if (i == 2 && NOempty) {
    tmp = getCell(c.coordNO());
    if(tmp != nullptr && tmp->getType() == '.'){ break; }
    else { NOempty = false; };
  }
  else if (i == 3 && NWempty) {
    tmp = getCell(c.coordNW());
    if(tmp != nullptr && tmp->getType() == '.'){ break; }
    else { NWempty = false; };
  }
  else if (i == 4 && SEempty) {
    tmp = getCell(c.coordSE());
    if(tmp != nullptr && tmp->getType() == '.'){ break; }
    else { SEempty = false; };
  }
  else if (i == 5 && SOempty) {
    tmp = getCell(c.coordSO());
    if(tmp != nullptr && tmp->getType() == '.'){ break; }
    else { SOempty = false; };
  }
  else if (i == 6 && SWempty) {
    tmp = getCell(c.coordSW());
    if(tmp != nullptr && tmp->getType() == '.'){ break; }
    else { SWempty = false; };
  }
  else if (i == 7 && WEempty){
    tmp = getCell(c.coordWE());
    if(tmp != nullptr && tmp->getType() == '.'){ break; }
    else { WEempty = false; };
  }
  else{
    i = rand()%(8);
  }
}
if (!EAempty && !NEempty && !NOempty && !NWempty &&
    !SEempty && !SOempty && !SWempty && !WEempty){
  dragonptr->modHP(-1000);
  dragonptr->assignCell(nullptr);
  return c;
} else {
  tmp->setType(dragonChar);
  tmp->setActor(dragonptr);
  dragonptr->assignCell(tmp);
  return  tmp->getCoord();
}
}


// returns true if this chamber has a stair
bool Chamber::hasStair() {
  for (auto &c : room) {
    if (c->getType() == '\\') {
      return true;
    }
  }
  return false;
}

// if t is a dragon Hoard, this function will 
// also spawn a Dragon beside the Hoard

void Chamber::addActorToChamber(std::shared_ptr<Actor> a){
  shared_ptr<Cell> randCell = nullptr;

  while(true){
    randCell = room[rand()%(cellNum)];

    if(randCell->getType() == '.'){
      a->assignCell(randCell);
      string aRace = a->getRace()->getId();
      char cellType = '.';
      if(aRace == "human" ){
        cellType = 'H';
      }
      else if(aRace == "dwarf") {
        cellType = 'W';
      } 
      else if(aRace == "elf"){
        cellType = 'E';
      }
      else if(aRace == "orc"){
        cellType = 'O';
      }
      else if(aRace == "merchant"){
        cellType = 'M';
      }
      else if(aRace == "dragon"){
        cellType = 'D';
      }
      else if(aRace == "halfling"){
        cellType = 'L';
      }
      else{
        cellType = '@';
      }
      randCell->setType(cellType);
      randCell->setActor(a);
      break;
    }

  }
}

void Chamber::addGoldToChamber(shared_ptr<Gold> g) {
  string GoldType = g->getType();
  auto randCell = std::make_shared<Cell>('.', 0, 0);

    if (GoldType == "DH") {
      while (true) {
        randCell = room[rand()%(cellNum)];
	if (randCell->getType() == '.') {
	  g->setCell(randCell);
          randCell->setType('G');
          randCell->setItem(g);
	  break;
	}
      };
cout << "start to add dragon" << endl;
      Coordinate DragonCoord = setCelltoDragon(g->getCell()->getCoord(), g->getDragon());
cout << "dragon added" << endl;      
    }
    else {
      while (true) {
        randCell = room[rand()%(cellNum)];
        if (randCell->getType() == '.') {
          g->setCell(randCell);
          randCell->setItem(g);
          randCell->setType('G');
          break;
	}
      }
    }
}

void Chamber::addPotionToChamber(shared_ptr<Potion> g){
    std::shared_ptr<Cell> randCell = nullptr;
    while (true) {
      randCell = room[rand()%(cellNum)];
      if (randCell->getType() == '.') {
        g->setCell(randCell);
        randCell->setItem(g);
        randCell->setType('P');
        randCell->setItem(g);
        break;
      }
    }
 }
