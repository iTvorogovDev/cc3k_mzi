#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <memory>
#include <string>
#include "../race/race.h"

class Cell;
class Item;

class Actor {
    //private variables
    int hp;

  //Private functions
  virtual int getAttackedByRace(std::shared_ptr<Race> r);
  virtual int attackRace(std::shared_ptr<Race> r);

protected:

  //Protected variables
  std::shared_ptr<Race> race;
  std::shared_ptr<Cell> curCell;

public:
  
  //Public functions
  Actor();
  std::shared_ptr<Cell> getCell() const;
  void changeRace(std::shared_ptr<Race> newRace);
  int getHP() const;
  int getAtk() const;
  int getDef() const;
  std::shared_ptr<Race> getRace() const;
  void modHP(const int val);
  int getAttacked(std::shared_ptr<Race> r);
  int attack(std::shared_ptr<Race> r);
  void assignCell(std::shared_ptr<Cell> newCell);	
  bool zeroHP() const;

};

class Player:public Actor {

  //Private variables
  int atkMod;
  int defMod;
  int maxHP;
  int score;
  std::vector<std::string> knownPotions;
  
public:
  //Public functions
  Player(std::shared_ptr<Race> newRace);
  int getAtkMod() const;
  int getDefMod() const;
  int getMaxHP() const;
  int getScore() const;
  void changeScore(const int val);
  void modAtkMod(const int val);
  void modDefMod(const int val);
  void resetAtkMod();
  void resetDefMod();
  void setKnownPotion(std::string type, int index);
  std::vector<std::string> getKnownPotions();

};

class NPC:public Actor {

  //Private variables
  std::shared_ptr<Item> drops;
  
public:

  //Public functions
  NPC(std::shared_ptr<Race> newRace, std::shared_ptr<Item> loot);
  std::shared_ptr<Item> getDrops();

};

#endif
