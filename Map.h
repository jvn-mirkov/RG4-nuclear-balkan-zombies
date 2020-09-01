#ifndef NBZ_MAP_H
#define NBZ_MAP_H

#include "ControlMatrix.h"

class Map {

public:
    Map();

    void renderMap();

    void renderBoxes(ControlMatrix *cm);

    void renderBombs(ControlMatrix *cm);

    void renderBombAnimationPart1(float x, float y);

    void renderBombAnimationPart2(float x, float y);

private:

};


#endif
