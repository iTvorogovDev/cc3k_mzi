#include "item.h"
#include "../dungeon/cell.h"
/*Item::Item(std::shared_ptr<Cell> aCell){
  c = aCell;
}*/

/*Item::~Item() {
}*/

void Item::setCell(std::shared_ptr<Cell> aCell){
  c = aCell;
  aCell->setType('G');
}

std::shared_ptr<Cell> Item::getCell() {
	return c;
};


