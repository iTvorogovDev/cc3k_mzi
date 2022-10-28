#include "actor.h"
#include "../race/race.h"

using namespace std;
//Actor class implementation

Actor::Actor(): hp{0} {}

void Actor::changeRace(shared_ptr<Race> newRace) {
    int mod = race->getHP();//get current HP
    race = newRace;
    mod = race->getHP() - mod;//get New races HP difference from current
    modHP(mod);//modify HP by that difference
}

shared_ptr<Cell> Actor::getCell() const {

  return curCell;

}

void Actor::assignCell(shared_ptr<Cell> newCell) {

  curCell = newCell;

}

int Actor::getHP() const {

  return hp;

}

int Actor::getAtk() const {
    return race->getAtk();
}

int Actor::getDef() const {
    return race->getDef();
}

shared_ptr<Race> Actor::getRace() const {

  return race;

}

void Actor::modHP(const int val) {
    hp += val;
    if (getRace()->getId() != "vampire") {
        if ( hp > getRace()->getHP()) hp = getRace()->getHP();
    }
}

bool Actor::zeroHP() const {

  if (hp <= 0) return true;
  else return false;

}

int Actor::getAttackedByRace(shared_ptr<Race> r) {

  return race->getAttacked(*r);

}

int Actor::attackRace(shared_ptr<Race> r) {

  return race->attack(*r);

}

int Actor::attack(shared_ptr<Race> r) {

  int damageDealt = attackRace(r);
  return damageDealt;

}

int Actor::getAttacked(shared_ptr<Race> r) {

  int damageReceived = getAttackedByRace(r);
  return damageReceived;

}

//Player class implementation

Player::Player(shared_ptr<Race> newRace): Actor{} {
  
  race = newRace;
  atkMod = 0;
  defMod = 0;
  score = 0;
  modHP(race->getHP());
  maxHP = race->getHP();
  knownPotions.resize(6);
  curCell = nullptr;

}

int Player::getAtkMod() const {

  return atkMod;

}

int Player::getDefMod() const {

  return defMod;

}

int Player::getMaxHP() const {

  return maxHP;

}

void Player::setKnownPotion(std::string type, int index) {

  knownPotions[index] = type;

}

int Player::getScore() const {

  return score;

}

std::vector<std::string> Player::getKnownPotions() {

  return knownPotions;

}

void Player::changeScore(const int val) {

  score += val;

}

void Player::modAtkMod(const int val) {

  atkMod += val;
  race->modAtk(val);

}

void Player::modDefMod(const int val) {

  atkMod += val;
  race->modDef(val);

}

void Player::resetAtkMod() {

  race->modAtk(-1 * atkMod);
  atkMod = 0;

}

void Player::resetDefMod() {

  race->modDef(-1 * defMod);
  defMod = 0;

}

//NPC implementation

NPC::NPC(shared_ptr<Race> newRace, shared_ptr<Item> loot) {

  race = newRace;
  drops = loot;
  modHP(race->getHP());
  curCell = nullptr;

}

shared_ptr<Item> NPC::getDrops() {

  return drops;

}

