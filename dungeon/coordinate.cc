#include "coordinate.h"

void Coordinate::setX(int newx) {
  x = newx;
}

void Coordinate::setY(int newy) {
  y = newy;
}

void Coordinate::setChamber_Belong(int newChamber_Belong) {
  chamber_belong = newChamber_Belong;
}

int Coordinate::getX() {
  return x;
}

int Coordinate::getY() {
  return y;
}

int Coordinate::getChamber_Belong(){
  return chamber_belong;
}

Coordinate Coordinate::coordNO() {
  int newx = x - 1;
  int newy = y;
	
  return Coordinate{ newx, newy };
}

Coordinate Coordinate::coordSO(){
  int newx = x + 1;
  int newy = y;

  return Coordinate{ newx, newy };
}

Coordinate Coordinate::coordEA() {
  int newx = x;
  int newy = y + 1;

  return Coordinate{ newx, newy };
}

Coordinate Coordinate::coordWE() {
  int newx = x;
  int newy = y - 1;
	 
  return Coordinate{ newx, newy };
}

Coordinate Coordinate::coordNE() {
  int newx = x - 1;
  int newy = y + 1;

  return Coordinate{ newx, newy };
};

Coordinate Coordinate::coordNW() {
  int newx = x - 1;
  int newy = y - 1;

  return Coordinate{ newx, newy };
}

Coordinate Coordinate::coordSE() {
  int newx = x + 1;
  int newy = y + 1;

  return Coordinate{ newx, newy };
}

Coordinate Coordinate::coordSW() {
  int newx = x + 1;
  int newy = y - 1;
	
  return Coordinate{ newx, newy };
}
