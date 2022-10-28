
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>
#include "floor.h"
#include "../actor/actor.h"
#include "../race/race.h"
#include "chamber.h"


using namespace std;

Floor::Floor(std::string mapName) :floorMap{ mapName } {
   srand((unsigned)time(NULL));
  const int gridCol = 79;
  const int gridRow = 25;

  chamberCount = 0;
  size = 80 * 25;
 for (int i = 0; i < gridRow; i++) {
   string line;
   getline(floorMap, line);
   grid.emplace_back(vector<shared_ptr<Cell>>());
   int j = 0;
      
     for(char type : line){
         grid[i].emplace_back(make_shared<Cell>(type, i, j));
            j++;
      }
    };

       grid[19][37]->setChamberBelong(5);

	for (int i = 0; i < gridRow; i++) {
		for (int j = 0; j < gridCol; j++) {
   
			if ( grid[i][j]->getType() == '.' && grid[i][j]->getCoord().getChamber_Belong() == 0){
				Coordinate curCoord = grid[i][j]->getCoord();
				if (this->getCell(curCoord.coordEA())->getCoord().getChamber_Belong() != 0) {
					grid[i][j]->setChamberBelong(
						this->getCell(curCoord.coordEA())->getCoord().getChamber_Belong());
				}//East

				else if (this->getCell(curCoord.coordNE())->getCoord().getChamber_Belong() != 0) {
					grid[i][j]->setChamberBelong(
						this->getCell(curCoord.coordNE())->getCoord().getChamber_Belong());
				}//North East

				else if (this->getCell(curCoord.coordNO())->getCoord().getChamber_Belong() != 0) {
					grid[i][j]->setChamberBelong(
						this->getCell(curCoord.coordNO())->getCoord().getChamber_Belong());
				}//North

				else if (this->getCell(curCoord.coordNW())->getCoord().getChamber_Belong() != 0) {
					grid[i][j]->setChamberBelong(
						this->getCell(curCoord.coordNW())->getCoord().getChamber_Belong());
				}//North West

				else if (this->getCell(curCoord.coordSE())->getCoord().getChamber_Belong() != 0) {
					grid[i][j]->setChamberBelong(
						this->getCell(curCoord.coordSE())->getCoord().getChamber_Belong());
				}//South East

				else if (this->getCell(curCoord.coordSO())->getCoord().getChamber_Belong() != 0) {
					grid[i][j]->setChamberBelong(
						this->getCell(curCoord.coordSO())->getCoord().getChamber_Belong());
				}//South

				else if (this->getCell(curCoord.coordSW())->getCoord().getChamber_Belong() != 0) {
					grid[i][j]->setChamberBelong(
						this->getCell(curCoord.coordSW())->getCoord().getChamber_Belong());
				}//South West

				else if (this->getCell(curCoord.coordWE())->getCoord().getChamber_Belong() != 0) {
					grid[i][j]->setChamberBelong(
						this->getCell(curCoord.coordWE())->getCoord().getChamber_Belong());
				}//West

				else {
					chamberCount++;
					grid[i][j]->setChamberBelong(chamberCount);
				}// None of its neighbours belong to a chamber, so the cell must be in a new chamber.
                             
			}
		
		}
	};

	for (int i = 0; i < chamberCount; i++) {
		chambers.push_back(Chamber(i + 1));
	};

	for (int i = 0; i < gridRow; i++) {
		for (int j = 0; j < gridCol; j++) {
			int chamberBelong = grid[i][j]->getCoord().getChamber_Belong();
			if (chamberBelong != 0) {
				chambers[chamberBelong - 1].pushCell(grid[i][j]);
			};
		}
	};
}

Floor::~Floor(){ };
int Floor::getFloorNumber() {
	return number;
}

int Floor::getSize() {
	return size;
}

vector<vector<shared_ptr<Cell>>> Floor::getAllUsefulCells(){
  vector <vector <shared_ptr<Cell>>> tmp;
  for(int i = 0; i < 5; i++){
    tmp.emplace_back(chambers[i].getRoom());
  } 
  return tmp;
}

std::vector<std::vector<shared_ptr<Cell>>> Floor::getGrid() {
	return grid;
}

// spawn the stair first
void Floor::stairSpawn() {
	int randomChamNum = rand()%(chamberCount);
	chambers[randomChamNum].setCell('\\');
}

// spawn of characters && gold stuff

void Floor::actorSpawn(std::shared_ptr<Actor> p) {
    string actorRace = p->getRace()->getId();
//cout << "add " << actorRace << endl;
    if(actorRace == "drow" || actorRace == "vampire" ||
       actorRace == "troll" || actorRace == "goblin" || actorRace == "shade"){
	int i = rand()%(chamberCount);

        while(chambers[i].hasStair()){
          i = rand()%(chamberCount);
        }
        chambers[i].addActorToChamber(p);
    }
    else {

        int randomChamNum = rand()%(chamberCount);
	chambers[randomChamNum].addActorToChamber(p);
    }
//cout << actorRace << " add compelet" << endl;
}

void Floor::potionSpawn(std::shared_ptr<Potion> p) {
cout << "add potion" << p->getPotionType() << endl;
	int chamberRand = rand()%(chamberCount);
	chambers[chamberRand].addPotionToChamber(p);
cout << p->getPotionType() << " added" << endl;
}

void Floor::goldSpawn(std::shared_ptr<Gold> g) {
	
//cout << "add gold" << g->getType() << endl;
	int chamberRand = rand()%(chamberCount);
	chambers[chamberRand].addGoldToChamber(g);
//cout << g->getType() << " added" << endl;
}

std::ostream &operator<<(std::ostream &out, const Floor &g) {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 79; j++) {
			out << g.grid[i][j]->getType();
		}
		out << std::endl;
	}
        return out;
}


