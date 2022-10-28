#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include "../dungeon/dungeon.h"
#include "observer.h"
#include <iostream>


class Display: public Observer {
std::ostream &out;
std::shared_ptr<Dungeon> dungeon;

void updateMap() const;
void updateText() const;

public:
Display(std::ostream &out, std::shared_ptr<Dungeon>);
~Display();
void notify() override;
void startMessage();
void endMessage();
};

static std::ostream & operator<<(std::ostream &, const Dungeon &d);

#endif
