#ifndef _RACE_H_
#define _RACE_H_
#include <string>

class Race {
int hp;
int atk;
int def;
const std::string id;
bool hostile;
bool hero;

  virtual bool isRaceHostile() const;
  virtual int getAttackedByRace(const Race &r) const;
  virtual int attackRace(const Race &r) const;
protected:
  int getAttackedByNormalRace(const Race &r) const;
  int getAttackedByProtagonist(const Race &r) const;
public:
  Race();
  Race(int hp, int atk, int def, std::string id, bool hostile, bool hero);
  virtual ~Race();
  int getAttacked(const Race &r) const;
  int attack(const Race &r) const;
  bool isHostile() const;
  void setHostile(bool hostile);
  int getHP() const;
  int getAtk() const;
  int getDef() const;
  std::string getId() const;
  bool isHero() const;
  void modHP(int change);
  void modAtk(int change);
  void modDef(int change);
};
#endif


#ifndef _SHADE_H_
#define _SHADE_H_
#include "race.h"

class Shade : public Race {
public:
Shade();
~Shade();
};
#endif

#ifndef _DROW_H_
#define _DROW_H_
#include "race.h"

class Drow : public Race {
public:
  Drow();
  ~Drow();
};
#endif

#ifndef _VAMPIRE_H_
#define _VAMPIRE_H_
#include "race.h"

class Vampire : public Race {
public:
  Vampire();
  ~Vampire();
};
#endif


#ifndef _TROLL_H_
#define _TROLL_H_
#include "race.h"

class Troll : public Race {
public:
Troll();
~Troll();
};
#endif

#ifndef _GOBIN_H_
#define _GOBIN_H_
#include "race.h"

class Goblin : public Race {
public:
  Goblin();
  ~Goblin();
};
#endif

#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "race.h"

class Human : public Race {
public:
	Human();
	~Human();
};

#endif

#ifndef _DWARF_H_
#define _DWARF_H_
#include "race.h"

class Dwarf : public Race {
public:
  Dwarf();
  ~Dwarf();
};

#endif

#ifndef _ELF_H_
#define _ELF_H_
#include "race.h"


class Elf : public Race {
public:
	Elf();
	~Elf();
};
#endif

#ifndef _ORC_H_
#define _ORC_H_
#include "race.h"

class Orc : public Race {
public:
	Orc();
	~Orc();
};
#endif

#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include "race.h"

class Merchant : public Race {
  bool isRaceHostile() const override;
public:
  static bool hostile_merchant;

  Merchant();
  ~Merchant();
  void makeHostile();
};
#endif

#ifndef _HALFLING_H_
#define _HALFLING_H_
#include "race.h"

class Halfling : public Race {
public:
	Halfling();
	~Halfling();
};

#endif

#ifndef _DRAGON_H_
#define _DRAGON_H_
#include "race.h"

class Dragon : public Race {
  bool dragon_hostile;
  bool isRaceHostile() const override;
public:
  Dragon();
  ~Dragon();
  void setHostile(bool hostile);
};
#endif
