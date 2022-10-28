#include "display.h"
#include <iostream>
#include <string>
#include <locale>
#include <iomanip>

using namespace std;

Display::Display(ostream &out, shared_ptr<Dungeon> dungeon): out{out}, dungeon{dungeon} {}

Display::~Display() {};

string capitalize(string name) {
    name[0] = toupper(name[0]);
    return name;
}

void Display::updateMap() const {
  out << *dungeon;
}

void Display::updateText() const {
int floorNumber = dungeon->getFloorNumber();
auto floor = dungeon->getFloor(floorNumber);
auto player = dungeon->getPlayer();
string action = dungeon->getState();
cout << "Race: ";
cout << setw(7);
cout << capitalize(player->getRace()->getId());
cout << " Gold: ";
cout << setw(3);
cout << player->getScore();
cout << setw(52);
cout << "Floor " << floorNumber + 1 << endl;
cout << "HP: " << setw(3) << player->getHP() << endl;
cout << "Atk: " << setw(2) << player->getAtk() << endl;
cout << "Def: " << setw(2) << player->getDef() << endl;
cout << "Action: " << action << endl;
}

void Display::notify() {
    cout << string(100, '\n');//clears screen
    updateMap();
    updateText();
}

void Display::startMessage() {

  cout << "Choose your race or enter q to chicken out!" << endl;
  cout << "Available races:" << endl;
  cout << "s - shade" << endl;
  cout << "d - drow" << endl;
  cout << "v - vampire" << endl;
  cout << "g - goblin" << endl;
  cout << "t - troll" << endl;

}

void Display::endMessage() {
	cout << string(100, '\n');//clears screen
    cout << "Your score was " << dungeon->getPlayer()->getScore() << endl;
}

static ostream & operator<<(ostream &out, const Dungeon &d) {
  auto floor = d.getFloor(d.getFloorNumber());
  out << *floor;
  return out;
}
