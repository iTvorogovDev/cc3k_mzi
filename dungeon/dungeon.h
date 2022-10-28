#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include "../display/observer.h"
#include "../display/subject.h"
#include "../actor/actor.h"
#include "floor.h"

class Dungeon : public Subject {
private:
  std::vector< shared_ptr<Floor> > floors;
  shared_ptr<Player> player; 
  std::string state;
  int currentFloor;

public:
  Dungeon(std::string, std::shared_ptr<Player>);
  ~Dungeon() = default;

  int getFloorNumber()const;
  shared_ptr<Floor> getFloor(int) const;
  void nextFloor();
  void prevFloor();
  shared_ptr<Player> getPlayer() const;
  void setState(std::string);
  std::string getState() const;

};
#endif // !
