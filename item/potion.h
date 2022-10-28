#ifndef __POTION_H_
#define __POTION_H_

#include "item.h"
#include <string>

class Potion : public Item {
private:
	std::string potionType;
	int atkMod;
	int defMod;
	int hpMod;

public:
	Potion(std::string, int, int, int);
	~Potion() = default;
  
  /*Positive Potions: 
	Restore health (RH): restore up to 10 HP 
	Boost Atk (BA): increase ATK by 5 
	Boost Def (BD): increase Def by 5 

	Negative Potions: 
	Poison health (PH): lose up to 10 HP 
	Wound Atk (WA): decrease Atk by 5 
	Wound Def (WD): decrease Def by 5*/

	std::string getPotionType();
	int getAtkMod();
	int getDefMod();
	int getHPMod();
//        void setCell(Cell &c) override;

};

#endif // !1
