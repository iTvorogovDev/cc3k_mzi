#ifndef _ITEM_H_
#define _ITEM_H_

#include <memory>
#include "../dungeon/coordinate.h"

class Cell;

class Item {
private:
	std::shared_ptr<Cell> c;

public:
// Item(std::shared_ptr<Cell>);
 virtual ~Item() = default;	
 std::shared_ptr<Cell> getCell();
 void setCell(std::shared_ptr<Cell>);
  // bind the cell with the item.
// virtual ~Item();

};
#endif // !_ITEM_H_
