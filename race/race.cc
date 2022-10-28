#include "race.h"
#include <cstdlib>
#include <string>
using namespace std;

Race::Race(): hp{1}, atk{1}, def{1}, id{"generic"}, hostile{false}, hero{false} {}

Race::Race(int hp, int atk, int def, string name, bool hostile, bool hero): hp{hp}, atk{atk}, def{def}, id{name}, hostile{hostile}, hero{hero} {}

Race::~Race() {}

static int ceiling(double x) {
    int ret = static_cast<int>(x);
    return ret == x ? ret : ret + 1;
}

int Race::getAttackedByNormalRace(const Race &r) const {
    if (rand() % 100 < 50) return 0;
    double result = 100.0 / (100.0 + r.getDef());
    result *= static_cast<double>(r.getAtk());
    return ceiling(result);
}

int Race::getAttackedByProtagonist(const Race &r) const {
    double result = 100.0 / (100.0 + r.getDef());
    result *= static_cast<double>(r.getAtk());
    return ceiling(result);
}

bool Race::isHero() const {return hero;}

int Race::getAttackedByRace(const Race &r) const {
  string id = r.getId();
  int damage;
  if (id != "elf" || this->getId() == "drow") {
    damage = r.isHero() ? getAttackedByProtagonist(r) : getAttackedByNormalRace(r);
  } else {
    damage = getAttackedByNormalRace(r) + getAttackedByNormalRace(r);
  }
  if (id == "orc" && this->getId() == "goblin") damage *= 1.5;
  if (this->getId() == "halfling" && (rand() % 100 < 50)) damage = 0;
  return damage;
}

int Race::getAttacked(const Race &r) const {
	return getAttackedByRace(r);
}

int Race::attackRace(const Race &r) const {
  string id = r.getId();
  if (this->getId() == "vampire") {
    if (id == "dwarf") return -5;
    return 5;
  }
  return 0;
}

int Race::attack(const Race &r) const {
	return attackRace(r);
}

bool Race::isRaceHostile() const {
    return hostile;
}

bool Race::isHostile() const {
	return isRaceHostile();
}

void Race::setHostile(bool newVal) {
	this->hostile = newVal;
}

int Race::getHP() const {return hp;}

int Race::getAtk() const {return atk;}

int Race::getDef() const {return def;}

string Race::getId() const {return id;}

void Race::modHP(int change) { hp += change;}

void Race::modAtk(int change) { atk += change;}

void Race::modDef(int change) { def += change;}


// class Dragon
bool Dragon::isRaceHostile() const {return dragon_hostile;}
Dragon::Dragon(): Race{150, 20, 20, "dragon", false, false}, dragon_hostile{false} {}
Dragon::~Dragon() {}

void Dragon::setHostile(bool hostile) { dragon_hostile = hostile;}


// class Drow
Drow::Drow(): Race{150, 25, 15, "drow", false, true} {}

Drow::~Drow() {}

// class Dwarf
Dwarf::Dwarf(): Race{100, 20, 30, "dwarf", true, false} {}
Dwarf::~Dwarf() {}

// class Elf
Elf::Elf(): Race{140, 30, 10, "elf", true, false} {}
Elf::~Elf() {}

// class Goblin
Goblin::Goblin(): Race{110, 15, 20, "goblin", false, true} {}

Goblin::~Goblin() {}

// class Halfling
Halfling::Halfling(): Race{100, 15, 20, "halfling", true, false} {}

Halfling::~Halfling() {}

// class Human
Human::Human(): Race{140, 20, 20, "human", true, false} {}

Human::~Human() {}


// class Merchant
bool Merchant::isRaceHostile() const {return hostile_merchant;}
Merchant::Merchant(): Race{30, 70, 5, "merchant", false, false} {}
Merchant::~Merchant() {}

void Merchant::makeHostile() { hostile_merchant = true; }

bool Merchant::hostile_merchant = false;

// class Orc

Orc::Orc(): Race{180, 30, 25, "orc", true, false} {}
Orc::~Orc() {}


// class shade
Shade::Shade(): Race{125, 25, 25, "shade", false, true} {}

Shade::~Shade() {}

// class troll

Troll::Troll(): Race{120, 25, 15, "troll", false, true} {}

Troll::~Troll() {}

// class Vampire
Vampire::Vampire(): Race{50, 25, 25, "vampire", false, true} {}

Vampire::~Vampire() {}

