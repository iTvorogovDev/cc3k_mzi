#ifndef __GOLD_H_
#define __GOLD_H_

#include "item.h"
#include <string>
#include <memory>

class Dragon;
class Actor;

class Gold : public Item {
private:
	std::string goldType;

/*  S: small Gold       1
	N: normal Gold		2
	DH: dragon Hoard    4
	MH: merchant Hoard  6 */
	 	
	bool hoard;
	int value;
	std::shared_ptr<Actor> dragon;

public:
	Gold(std::string, std::shared_ptr<Actor>);
	~Gold() = default;
	
	void setDragon(std::shared_ptr<Actor>);
	std::string getType();
	bool isHoard();
	int getValue();
	std::shared_ptr<Actor> getDragon();
//        void setCell(std::shared_ptr<Cell>) override;
};

#endif // !__GOLD_H_
