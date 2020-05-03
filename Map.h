#ifndef NBZ_MAP_H
#define NBZ_MAP_H
#include "ControlMatrix.h"

class Map {

public:
    Map();
    void renderMap();
    void renderBoxes(ControlMatrix *cm);
    void renderBombs(ControlMatrix *cm);

private:

};


#endif
