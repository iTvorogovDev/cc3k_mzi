#ifndef CONTROLLER_H
#define CONTROLLER_H

#include<string>
#include<vector>
#include "../dungeon/dungeon.h"

class Controller {
  //Private functions
  void movePlayer(std::string direction);
  std::string enemiesTurn();
  void moveNPC(std::shared_ptr<NPC> actor);
  bool playerClose(std::shared_ptr<NPC> actor);
  std::string objectsClose(std::shared_ptr<Player> player, std::string);

  //Private variables
  std::shared_ptr<Dungeon> dungeon;
  std::vector<std::shared_ptr<Actor>> enemies;
  std::vector<std::shared_ptr<Item>> potions;
  std::vector<std::shared_ptr<Item>> gold;
  std::vector<std::shared_ptr<NPC>> dragons;
  bool isPaused;
  bool finished;
  bool restart_game;
  
public:
  //Public functions
  void attack();
  void chooseRace(std::string arg);
  bool isDone();
  bool doRestart();
  void raceCommands(char);
  void moveCommands(std::string);
  void changeStateCommands(std::string);
  void gameCommands(std::string);
  int solicitInput();
  void notifyDungeon();
  void start();
  void pause();
  void restart();
  void finish();
  void quit();
  void generateEnemies();
  void generatePotions();
  void generateGold();
  void actorSpawn();
  void potionSpawn();
  void goldSpawn();
  void attack(std::string direction);
  void usePotion(std::string direction);
  Controller(std::shared_ptr<Dungeon> newDungeon);
  ~Controller();

};

#endif
