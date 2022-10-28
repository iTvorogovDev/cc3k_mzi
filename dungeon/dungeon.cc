#include "dungeon.h"
#include "../actor/actor.h"
#include <string>

using namespace std;

Dungeon::Dungeon(string name, shared_ptr<Player> playerptr) {
  for(int i = 0; i < 5; i++){
    floors.emplace_back(make_shared<Floor>(name));
  }
  player = playerptr;
 currentFloor = 0;
}

int Dungeon::getFloorNumber() const{
  return currentFloor;
}

shared_ptr<Floor> Dungeon::getFloor(int floorNum) const {
  return floors[floorNum];
}

void Dungeon::nextFloor() { ++currentFloor; }

void Dungeon::prevFloor() { --currentFloor; }

shared_ptr<Player> Dungeon::getPlayer() const {
  return player;
}

void Dungeon::setState(string state) {
    this->state = state;
}

string Dungeon::getState() const {
    return state;
}
