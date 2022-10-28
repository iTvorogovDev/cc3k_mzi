#ifndef __CHAMBER_H_
#define __CHAMBER_H_

#include <memory>
#include <vector>
//#include "../display/subject.h"
#include "coordinate.h"

class Gold;
class Potion;
class Cell;
class Item;
class Actor;


class Chamber {
private:
	std::vector< std::shared_ptr<Cell> > room;
	int chamberNum;
	int cellNum;
	std::shared_ptr<Cell> getCell(Coordinate);
	
public:
 	
	Chamber(int );
	~Chamber();
	
	int getCellNum(){ return cellNum;};	

	void pushCell(std::shared_ptr<Cell>); // push a cell into 'room'

	void setCell(char); 
/*set a cell to the given type by generating a random number
	 from 0 to cellNum, it will keep generating new random 
	 numbers until find a valid cell.*/
	
	std::vector< std::shared_ptr<Cell> >getRoom();
	Coordinate setCelltoDragon(Coordinate, std::shared_ptr<Actor>);
/*the Coordinate taken in this function is where the dragon 
hoard is spawned.*/
	
	bool hasStair();
/* Map/type Contents:
	'|' '-' : Walls
	'+'     : Doorways
	'#'	 : Passages
	'.'	 : FloorTiles
	'P'	 : Potion

	Enemies
	'H'	 : Human
	'W'     : Dwarf
	'E'     : Elf
	'O'     : Orc
	'M'     : Merchant
	'D'     : Dragon
	'L'     : Halfling

	'@'     : Player */

	void addGoldToChamber(std::shared_ptr<Gold>);
  	void addPotionToChamber(std::shared_ptr<Potion>);
	void addActorToChamber(std::shared_ptr<Actor>);
};
#endif // !1
