#include "Coord.h"
using namespace ISOENG::UTILS;

Coord::Coord()
{
  x = 0; y = 0;
}
Coord::Coord(int _x, int _y)
{
  x = x; y = y;
}
Coord Coord::ToIso(Coord tileSize)
{
  Coord tempPt;

  tempPt.x = (x - y) * tileSize.x;
  tempPt.x = (x + y) * tileSize.y;

  return tempPt;
}
