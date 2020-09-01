#ifndef NBZ_BOMB_H
#define NBZ_BOMB_H

#include "ControlMatrix.h"

class Bomb {

public:
    Bomb(float x, float y);

    ~Bomb();

    void Tick();

    int getTime() const;

    float getX() const;

    float getY() const;

    void destroyBomb(ControlMatrix *cm, int bombX, int bombY);

private:
    float x;
    float y;
    int time;

};


#endif
