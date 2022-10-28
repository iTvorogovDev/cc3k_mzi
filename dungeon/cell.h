#ifndef _CELL_H_
#define _CELL_H_

#include "../display/subject.h"
//#include "../display/observer.h"
#include "coordinate.h"
#include <string>
#include <memory>

class Actor;
class Item;


class Cell{
public:
	Cell();
	Cell(char, int, int);
	~Cell();

// getters


	char getType();
//        void resetBaseType();
	Coordinate getCoord(); // get the coordinate of the cell

	bool isPlayerMovable();
	bool isNPCMovable(); 

        void setbaseType(char type);
	void setType(char type);
	void setItem(std::shared_ptr<Item>);

	void actorDead(std::string actorRace);
	void setActor(std::shared_ptr<Actor>);

        std::shared_ptr<Actor> getActor();
        std::shared_ptr<Item> getItem();

 	void reset(); // this set the cell to its base type.
	void itemTaken(std::string itemtype);
	void setPos(int newx, int newy);
	void setChamberBelong(int newChamberNum);

        

private:

	char type;
	char baseType;
	Coordinate pos;
	std::shared_ptr<Item> i;
        std::shared_ptr<Actor> a;
/* Map/type Contents:
	 '|' '-' : Walls
	 '+'     : Doorways
	 '#'	 : Passages
	 '.'	 : FloorTiles
	 'P'	 : Potion
	 'G'	 : Gold/Hoard

   Enemies
	 'H'	 : Human
	 'W'     : Dwarf
	 'E'     : Elf
	 'O'     : Orc
	 'M'     : Merchant
	 'D'     : Dragon
	 'L'     : Halfling 
	
	 '@'     : Player */
};

#endif // !_CELL_H_
