#ifndef _COORD_
#define _COORD_

namespace ISOENG
{
  namespace UTILS
  {
    class Coord
    {
      private:
      public:
        Coord ();
        Coord (int _x, int _y);
        Coord ToIso(Coord tileSize);

        int x, y;
    };
  }
}

#endif
