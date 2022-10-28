#ifndef __COORDINATE_H_
#define __COORDINATE_H_

class Coordinate{
private:
  int x;
  int y;
  int chamber_belong;

public:
  Coordinate(int x, int y) :x{ x }, y{ y } { chamber_belong = 0; };
  ~Coordinate() = default;

  void setX(int);
  void setY(int);
  void setChamber_Belong(int);

  int getX();
  int getY();
  int getChamber_Belong();

// These function get the coordiante for the corresponding
// position to the current coordinate.

  Coordinate coordNO(); // north
  Coordinate coordSO(); // south
  Coordinate coordEA(); // east
  Coordinate coordWE(); // west
  Coordinate coordNE(); // north-east
  Coordinate coordNW(); // north-west
  Coordinate coordSE(); // south-east
  Coordinate coordSW(); // south-west
};


#endif
