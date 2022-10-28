#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "controller.h"
#include "../dungeon/cell.h"

Controller::Controller(std::shared_ptr<Dungeon> newDungeon): dungeon {newDungeon}, finished{false}, restart_game{false} {}

void Controller::usePotion(std::string direction) {

  std::string message;
  std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(dungeon->getPlayer());
  Coordinate coord = player->getCell()->getCoord();

  if (direction == "no") {

    coord = coord.coordNO();

  } else if (direction == "so") {

    coord = coord.coordSO();

  } else if (direction == "ea") {

    coord = coord.coordEA();

  } else if (direction == "we") {

    coord = coord.coordWE();

  } else if (direction == "ne") {

    coord = coord.coordNE();

  } else if (direction == "nw") {

    coord = coord.coordNW();

  } else if (direction == "se") {

    coord = coord.coordSE();

  } else if (direction == "sw") {

    coord = coord.coordSW();

  }
  
  std::shared_ptr<Cell> cell = dungeon->getFloor(dungeon->getFloorNumber())->getCell(coord);
  std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(cell->getItem());
  if (potion) {

    player->modHP(potion->getHPMod());
    player->modAtkMod(potion->getAtkMod());
    player->modDefMod(potion->getDefMod());
    cell->reset();
    if (potion->getAtkMod() > 0) {
      message += "The potion boosts your attack for " + std::to_string(potion->getAtkMod()) + " points.";
      player->setKnownPotion("BA", 0);
    } else if (potion->getAtkMod() < 0) {
      message += "The potion wounds your attack for " + std::to_string(potion->getAtkMod()) + " points.";
      player->setKnownPotion("WA", 1);
    } else if (potion->getDefMod() > 0) {
      message += "The potion boosts your defence for " + std::to_string(potion->getDefMod()) + " points.";
      player->setKnownPotion("BD", 2);
    } else if (potion->getDefMod() < 0) {
      message += "The potion wounds your defence for " + std::to_string(potion->getDefMod()) + " points.";
      player->setKnownPotion("WD", 3);
    } else if (potion->getHPMod() > 0) {
      message += "The potion heals you for " + std::to_string(potion->getHPMod()) + " HP.";
      player->setKnownPotion("RH", 4);
    } else if (potion->getHPMod() < 0) { 
      message += "The potion poisons you for " + std::to_string(potion->getHPMod()) + " HP.";
      player->setKnownPotion("PH", 5);
    }
    dungeon->setState(message);
    dungeon->notifyObservers();
    
  }

}

void Controller::attack(std::string direction) {

  std::shared_ptr<Actor> player = dungeon->getPlayer();
  Coordinate coord = player->getCell()->getCoord();

  if (direction == "no") {

    coord = coord.coordNO();

  } else if (direction == "so") {

    coord = coord.coordSO();

  } else if (direction == "ea") {

    coord = coord.coordEA();

  } else if (direction == "we") {

    coord = coord.coordWE();

  } else if (direction == "ne") {

    coord = coord.coordNE();

  } else if (direction == "nw") {

    coord = coord.coordNW();

  } else if (direction == "se") {

    coord = coord.coordSE();

  } else if (direction == "sw") {

    coord = coord.coordSW();

  } else {
    dungeon->setState("The direction " + direction + " is invalid");
    dungeon->notifyObservers();
    return;
  }
  dungeon->getFloor(dungeon->getFloorNumber());
  std::shared_ptr<Cell> cell = dungeon->getFloor(dungeon->getFloorNumber())->getCell(coord);
  std::shared_ptr<Actor> actor = cell->getActor();
  if (actor) {
    if (actor->getRace()->getId() == "merchant") std::static_pointer_cast<Merchant>(actor->getRace())->makeHostile();
    if (player->getRace()->getId() == "troll") player->modHP(5);
    int healthGained = player->attack(actor->getRace());
    int damageDealt = actor->getAttacked(player->getRace());
    player->modHP(healthGained);
    std::cout << "player's health modified" << std::endl;
    actor->modHP(-1 * damageDealt);
    std::cout << "enemies health changed" << std::endl;
    std::string message;
    if (damageDealt != 0) {
        message = "You attacked the " + actor->getRace()->getId() + " and dealt " + std::to_string(damageDealt) + " points of damage.";
        if (actor->zeroHP()) {
            message += " The enemy is killed!";
        }
    } else {
        message = "You missed when attacking the " + actor->getRace()->getId() + ".";
    }
    if (healthGained == 5) {
        message += "\n        You gained 5 health through your attack.";
    } else if (healthGained == -5) {
        message += "\n        You lost 5 health through your attack.";
    }
    if (actor->getHP() < 0) {
    
      actor->assignCell(nullptr);
      cell->reset();
      if (actor->getRace()->getId() != "human" && actor->getRace()->getId() != "dragon" && actor->getRace()->getId() != "merchant") {
        std::shared_ptr<NPC> npc = std::dynamic_pointer_cast<NPC>(actor);
        std::shared_ptr<Gold> pile = std::dynamic_pointer_cast<Gold>(npc->getDrops());
        std::dynamic_pointer_cast<Player>(player)->changeScore(pile->getValue());
      if (actor->getRace()->getId() == "merchant") {
        std::dynamic_pointer_cast<Player>(player)->changeScore(4);
      }
      }
      else if (actor->getRace()->getId() == "human") {
      
        std::shared_ptr<Gold> pile1 = make_shared<Gold>("N", nullptr);
	std::shared_ptr<Gold> pile2 = make_shared<Gold>("N", nullptr);
        pile1->setCell(cell);
        cell->setType('G');
        cell->setItem(pile1);
        Coordinate coord = cell->getCoord();
        for (int i = 0; i < 8; ++i) {

          if (i == 0) {
            coord = coord.coordNO();
          }
          else if (i == 1) { coord = coord.coordSO(); }
          else if (i == 2) { coord = coord.coordWE(); }
          else if (i == 3) { coord = coord.coordEA(); }
          else if (i == 4) { coord = coord.coordSW(); }
          else if (i == 5) { coord = coord.coordSE(); }
          else if (i == 6) { coord = coord.coordNE(); }
          else if (i == 7) { coord = coord.coordNW(); }
          std::shared_ptr<Cell> newCell = dungeon->getFloor(dungeon->getFloorNumber())->getCell(coord);
          if (newCell->isNPCMovable()) {

            newCell->setType('G');
            newCell->setItem(pile2);
            pile2->setCell(newCell);
            break;

          }

        }

      }
      
    }    
    message += "\n" + enemiesTurn();
    dungeon->setState(message);

  }else {
      dungeon->setState("There is nobody to attack there");
  }
  dungeon->notifyObservers();
}

void Controller::movePlayer(std::string direction){
  Coordinate coord = dungeon->getPlayer()->getCell()->getCoord();
  Coordinate newCoord {-1, -1};
  std::string message;

  if (direction == "no") {

    newCoord = coord.coordNO();
    message += "north";

  } else if (direction == "so") {

    newCoord = coord.coordSO();
    message += "south";

  } else if (direction == "ea") {

    newCoord = coord.coordEA();
    message += "east";

  } else if (direction == "we") {

    newCoord = coord.coordWE();
    message += "west";

  } else if (direction == "ne") {

    newCoord = coord.coordNE();
    message += "northeast";

  } else if (direction == "nw") {

    newCoord = coord.coordNW();
    message += "northwest";

  } else if (direction == "se") {

    newCoord = coord.coordSE();
    message += "southeast";

  } else if (direction == "sw") {

    newCoord = coord.coordSW();
    message += "southwest";

  }

  std::shared_ptr<Player> player = dungeon->getPlayer();
  std::shared_ptr<Cell> newCell = dungeon->getFloor(dungeon->getFloorNumber())->getCell(newCoord);
  std::shared_ptr<Cell> curCell = player->getCell();

  if (newCell->isPlayerMovable()) {

    curCell->reset();
    newCell->setType('@');
    newCell->setActor(player);
    player->assignCell(newCell);
    message += ", and ";
    message += objectsClose(player, direction);
    if (player->getRace()->getId() == "troll") player->modHP(5);

    if (isPaused == false) message += "\n" + enemiesTurn();
    dungeon->setState(message);

  } else if (std::dynamic_pointer_cast<Gold>(newCell->getItem())) {
    
    std::shared_ptr<Gold> pile = std::dynamic_pointer_cast<Gold>(newCell->getItem());
    if (!(pile->getDragon())) {
      player->changeScore(pile->getValue());
      newCell->reset();
      newCell->setType('@');
      newCell->setActor(player);
      player->assignCell(newCell);
      curCell->reset();
      if (player->getRace()->getId() == "troll") player->modHP(5);
    } else {
      message += "\nThe dragon snaps at your fingers as you reach for his hoard";
      dungeon->setState(message);
    }

  } else if (newCell->getType() == '\\') {

    dungeon->nextFloor();
    generateEnemies();
    generatePotions();
    generateGold();
    dungeon->getFloor(dungeon->getFloorNumber())->actorSpawn(player);
    dungeon->getFloor(dungeon->getFloorNumber())->stairSpawn();
    if (player->getRace()->getId() == "troll") player->modHP(5);

  } else if (newCell->getItem()) {
      message = "Looking " + message + " the " + player->getRace()->getId() + " ";
      message += objectsClose(player, direction);
      dungeon->setState(message);
  } else if (newCell->getActor()) {
      message = "Looking " + message + " you see an enemy";
      dungeon->setState(message);
  } else {

    dungeon->setState("You can't move there");

  }

  dungeon->notifyObservers();

}

std::string Controller::objectsClose(std::shared_ptr<Player> player, std::string direction) {

  std::string message = "sees";
  Coordinate coord = player->getCell()->getCoord();
  int x = coord.getX();
  int y = coord.getY();

  if (direction == "no" || direction == "ne" || direction == "nw") --x;
  if (direction == "ne" || direction == "ea" || direction == "se") ++y;
  if (direction == "sw" || direction == "so" || direction == "se") ++x;
  if (direction == "sw" || direction == "we" || direction == "nw") --y;

  Coordinate curCoord = {x, y};
  std::shared_ptr<Cell> curCell = dungeon->getFloor(dungeon->getFloorNumber())->getCell(curCoord);
  if (curCell->getItem()) {
      std::cout << "found item" << std::endl;
        std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(curCell->getItem());
        if (potion) {
        
          std::vector<std::string> knownPotions = player->getKnownPotions();
          std::string potionType = potion->getPotionType();
          std::string potionName;
          if (potionType == "RH") {

            potionName = "Restore Health Potion";  

          } else if (potionType == "BA") {

            potionName = "Boost Attack Potion";

	  	  } else if (potionType == "BD") {

	    potionName = "Boost Defence Potion";

          } else if (potionType == "PH") {

	    potionName = "Poison Health Potion";

          } else if (potionType == "WA") {

	    potionName = "Wound Attack Potion";

          } else if (potionType == "WD") {

            potionName = "Wound Defence Potion";

          }
          std::cout << "found potion names" << std::endl;
          
          if (find(knownPotions.begin(), knownPotions.end(), potionType) != knownPotions.end()) {
	      message += ": " + potionName;
          } else {
              message += ": Unknown Potion";
          }
        } else {
            message += ": ";
            std::string type = static_pointer_cast<Gold>(curCell->getItem())->getType();
            if (type == "S") {
                message += "a small pile of treasure";
            } else if (type == "N") {
                message += "a normal pile of treasure";
            } else if (type == "MH") {
                message += "the treasure from the killed merchant";
            } else {
                message += "a dragon's treasure hoard";
            }
        }
  } else if (curCell->getActor()) {
        std::cout << "found actor" << std::endl;
        std::shared_ptr<NPC> actor = std::dynamic_pointer_cast<NPC>(curCell->getActor());
        if (actor) {
            message += ": a " + actor->getRace()->getId();
        }
  }
      
  if (message == "sees") {

    return "sees nothing";

  } else return message;

}

void Controller::moveNPC(std::shared_ptr<NPC> actor) {

  std::vector<std::shared_ptr<Cell>> validCells;
  Coordinate coord = actor->getCell()->getCoord();
  std::shared_ptr<Cell> curCell = actor->getCell();
  int x = coord.getX();
  int y = coord.getY();
  for (int i = x - 1; i <= x + 1; ++i) {

    for (int j = y - 1; j <= y + 1; ++j) {
  
      Coordinate newCoord = {i, j};

      std::shared_ptr<Cell> newCell = dungeon->getFloor(dungeon->getFloorNumber())->getCell(newCoord);
      if (newCell->isNPCMovable()) validCells.emplace_back(newCell);

    } 

  }
  
  if (validCells.size() > 0) {
    
    int rand = std::rand() % validCells.size();
    actor->assignCell(validCells[rand]);
    validCells[rand]->setType(curCell->getType());
    curCell->reset();
    validCells[rand]->setActor(actor);
  }

}

bool Controller::playerClose(std::shared_ptr<NPC> actor) {

  Coordinate actorCoord = actor->getCell()->getCoord();
  Coordinate playerCoord = dungeon->getPlayer()->getCell()->getCoord(); 
  int actorX = actorCoord.getX();
  int actorY = actorCoord.getY();
  int playerX = playerCoord.getX();
  int playerY = playerCoord.getY();
  for (int i = actorX - 1; i <= actorX + 1; ++i) {

    for (int j = actorY - 1; j <= actorY + 1; ++j) {

      if (playerX == i && playerY == j) return true;

    }

  }

  return false;

}

std::string Controller::enemiesTurn() {
  std::string message;
  std::cout << "Enemies Turn" << std::endl;
  std::vector<std::vector<std::shared_ptr<Cell>>> allCells = dungeon->getFloor(dungeon->getFloorNumber())->getAllUsefulCells();
  for (int i = 0; i < allCells.size(); ++i) {
 
    for (int j = 0; j < allCells[i].size(); ++j) {

      std::shared_ptr<NPC> curNPC = std::dynamic_pointer_cast<NPC>(allCells[i][j]->getActor());
      if (curNPC != nullptr && curNPC->getRace()->getId() != "dragon") {
        if (playerClose(curNPC) && curNPC->getRace()->isHostile()) {

          if (curNPC->getRace()->getId() == "merchant") std::cout << "merchant attacks" << std::endl;

          int damageToPlayer = dungeon->getPlayer()->getAttacked(curNPC->getRace());
          int healthGained = curNPC->attack(dungeon->getPlayer()->getRace());
          dungeon->getPlayer()->modHP(-1 * damageToPlayer);
          curNPC->modHP(-1 * healthGained);
          if (dungeon->getPlayer()->zeroHP()) finish();
          if (damageToPlayer > 0) {
            message += curNPC->getRace()->getId() + " attacks to deal " + std::to_string(damageToPlayer) + " damage!\n";
          } else {
            message += "You laugh as " + curNPC->getRace()->getId() + "'s attack barely misses you!\n";
          }

        } else moveNPC(curNPC);

      }
    
    }

  }

  for (int i = 0; i < dragons.size(); ++i) {

    if (playerClose(dragons[i])) {
      dragons[i]->getRace()->setHostile(true);
      int damageToPlayer = dungeon->getPlayer()->getAttacked(dragons[i]->getRace());
      if (damageToPlayer > 0) {
        message += "\nDragon roasts you for " + std::to_string(damageToPlayer) + " damage!";
      } else {
        message += "\nDragon has lung problems and coughs instead of breathing flames.\nRemember, kids, smoking is bad!\n";
      }
      dungeon->getPlayer()->modHP(-1 * damageToPlayer);
    }
  }
  if (dungeon->getPlayer()->zeroHP()) finish();
  return message;
}

void Controller::generateEnemies() {

  int rand;
  if (dungeon->getFloorNumber() > 0) enemies.clear();

  for (int i = 0; i < 20; ++i) {
    
    std::shared_ptr<Actor> newEnemy;
    std::shared_ptr<Race> newRace;
    rand = std::rand() % 18 + 1;

    if (rand >= 1 && rand <= 4) {
      
      newRace = make_shared<Human>();

    } else if (rand >= 5 && rand <= 7) {
 
      newRace = make_shared<Dwarf>();

    } else if (rand >= 8 && rand <= 12) {

      newRace = make_shared<Halfling>();

    } else if (rand >= 13 && rand <= 14) {

      newRace = make_shared<Elf>();

    } else if (rand >= 15 && rand <= 16) {

      newRace = make_shared<Orc>();

    } else if (rand >= 17 && rand <= 18) {
  
      newRace = make_shared<Merchant>();

    }
 
    if ((rand >= 1 && rand <= 4) || (rand >= 17 && rand <= 18)) {

      newEnemy = make_shared<NPC>(newRace, nullptr);  

    } else {
      
      std::shared_ptr<Item> newPile = nullptr;
      rand = std::rand() % 2 + 1;
      if (rand == 1) {

        newPile = make_shared<Gold>("N", nullptr);     

      } else {

        newPile = make_shared<Gold>("S", nullptr);

      }
      newEnemy = make_shared<NPC>(newRace, newPile);

    }
    
    if (dungeon->getFloorNumber() == 0) {

      enemies.emplace_back(newEnemy);    

    } else {

      enemies[i] = newEnemy;

    }

  }
  actorSpawn();
 
}

void Controller::generatePotions() {

  int rand;
  if (dungeon->getFloorNumber() > 0) potions.clear();

  for (int i = 0; i < 10; ++i) {

    std::shared_ptr<Item> newPotion = nullptr;
    rand = std::rand() % 6 + 1;

    if (rand == 1) {

      newPotion = make_shared<Potion>("RH", 10, 0, 0);          

    } else if (rand == 2) {

      newPotion = make_shared<Potion>("BA", 0, 5, 0);

    } else if (rand == 3) {

      newPotion = make_shared<Potion>("BD", 0, 0, 5);

    } else if (rand == 4) {

      newPotion = make_shared<Potion>("PH", -10, 0, 0);

    } else if (rand == 5) {

      newPotion = make_shared<Potion>("WA", 0, -5, 0);

    } else if (rand == 6) {

      newPotion = make_shared<Potion>("WD", 0, 0, -5);

    }

    if (dungeon->getFloorNumber() == 0) {
      potions.emplace_back(newPotion);
    } else {
      potions[i] = newPotion;
    }

  }
  potionSpawn();

}

void Controller::generateGold() {

  int rand;
  if (dungeon->getFloorNumber() > 0) gold.clear();
  dragons.clear();
  dragons.resize(0);

  for (int i = 0; i < 10; ++i) { 

    std::shared_ptr<Item> newPile;    
    rand = std::rand() % 8 + 1;
    if (rand >= 1 && rand <= 5) {

      newPile = make_shared<Gold>("N", nullptr);

    } else if (rand >= 6 && rand <= 7) {

      newPile = make_shared<Gold>("S", nullptr);

    } else if (rand == 8) {

      std::shared_ptr<Race> dragonRace = make_shared<Dragon>();
      std::shared_ptr<NPC> newDragon = make_shared<NPC>(dragonRace, nullptr);
      newPile = make_shared<Gold>("DH", newDragon);
      dragons.emplace_back(newDragon);

    }
    if (dungeon->getFloorNumber() == 0) {
      gold.emplace_back(newPile);
    } else {
      gold[i] = newPile;
    }

  }
  goldSpawn();
}

void Controller::actorSpawn() {

  std::shared_ptr<Floor> curFloor = dungeon->getFloor(dungeon->getFloorNumber());
  for (int i = 0; i < 20; ++i) {

    curFloor->actorSpawn(enemies[i]);
 
  }  

}

void Controller::potionSpawn() {
  std::cout << "Spawning potions" << std::endl;
  std::shared_ptr<Floor> curFloor = dungeon->getFloor(dungeon->getFloorNumber());
  for (int i = 0; i < 10; ++i) {
    
    std::shared_ptr<Potion> potion = std::dynamic_pointer_cast<Potion>(potions[i]);
    curFloor->potionSpawn(potion);

  }

}

void Controller::goldSpawn() {
  std::cout << "Spawning gold" << std::endl;
  std::shared_ptr<Floor> curFloor = dungeon->getFloor(dungeon->getFloorNumber());
  for (int i = 0; i < 10; ++i) {

    curFloor->goldSpawn(std::dynamic_pointer_cast<Gold>(gold[i]));

  }
  
}

void Controller::chooseRace(std::string arg) {

  std::shared_ptr<Race> newRace;

  if (arg == "shade") {
  
    newRace = make_shared<Shade>();

  } else if (arg == "drow") {

    newRace = make_shared<Drow>();

  } else if (arg == "vampire") {

    newRace = make_shared<Vampire>();

  } else if (arg == "goblin") {

    newRace = make_shared<Goblin>();

  } else if (arg == "troll") {

    newRace = make_shared<Troll>();

  }
  dungeon->getPlayer()->changeRace(newRace);

}

void Controller::pause() {

  if (isPaused == false) isPaused = true;
  else isPaused = false;

}

void Controller::finish() {
    
	finished = true;
	
}

bool Controller::isDone() {
    return finished;
}

bool Controller::doRestart() {

	return restart_game;
	
}

void Controller::restart() {
	
	restart_game = true;

}

void Controller::raceCommands(char input) {
  srand(time(NULL));
  std::cout << "Race Commands Called" << std::endl;
  if (input == 's') {

    dungeon->getPlayer()->changeRace(make_shared<Shade>());

  } else if (input == 'd') {

    dungeon->getPlayer()->changeRace(make_shared<Drow>());

  } else if (input == 'v') {

    dungeon->getPlayer()->changeRace(make_shared<Vampire>());

  } else if (input == 'g') {

    dungeon->getPlayer()->changeRace(make_shared<Goblin>());

  } else if (input == 't') {

    dungeon->getPlayer()->changeRace(make_shared<Troll>());

  }
  start();

}

void Controller::moveCommands(string input) {

    movePlayer(input);

}

void Controller::changeStateCommands(std::string input) {

  if (input == "f") {

    pause();

  } else if (input == "r") {

    restart();

  } else if (input == "q") {

    quit();

  } 

}


void Controller::gameCommands(std::string input) {

  std::string direction;
  std::cin >> direction;

  std::cout << "direction is " << direction <<  std::endl;

  if (input == "a") {

    attack(direction);

  } else if (input == "u") {

    usePotion(direction);

  }

}

void Controller::start() {

  dungeon->getFloor(dungeon->getFloorNumber())->stairSpawn();
  dungeon->getFloor(dungeon->getFloorNumber())->actorSpawn(dungeon->getPlayer());
  generatePotions();
  generateGold();
  generateEnemies();
  isPaused = false;
  dungeon->notifyObservers();

}

void Controller::quit() {

}

void Controller::notifyDungeon() {


}

Controller::~Controller() {


}

