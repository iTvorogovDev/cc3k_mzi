#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <fstream>
#include <vector>

#include "../display/observer.h"
#include "coordinate.h"
#include "cell.h"
#include "../item/potion.h"
#include "../item/gold.h"

class Actor;
class Chamber;

class Floor{
private:
	std::ifstream floorMap;

	int number;
	int chamberCount;
	std::vector<Chamber> chambers;
	std::vector<std::vector< std::shared_ptr<Cell> >> grid{};
	int size; //total number of cell.

	int PotionTotalNum;
	int enemyTotalNum;

public:
	Floor(std::string);
	~Floor();

	std::shared_ptr<Cell> getCell(Coordinate c) { return grid[c.getX()][c.getY()]; };
	
	std::vector <std::vector< std::shared_ptr<Cell>>> getAllUsefulCells(); 
 	
	
	int getFloorNumber();
	int getSize();
	std::vector<std::vector<std::shared_ptr<Cell>>> getGrid();

	void actorSpawn(std::shared_ptr<Actor> );
	void stairSpawn();
	void potionSpawn(std::shared_ptr<Potion> );
	void goldSpawn(std::shared_ptr<Gold>);

// display floor
	friend std::ostream  &operator<<(std::ostream&, const Floor &);
};
#endif // !_FLOOR_H)
