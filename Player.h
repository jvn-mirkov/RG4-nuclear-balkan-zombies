#ifndef NBZ_PLAYER_H
#define NBZ_PLAYER_H

#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<vector>
#include "ControlMatrix.h"

class Player {
public:
    Player(float xStart, float yStart, char playerNum);

    void setX(float x);

    void setY(float y);

    void renderPlayer();

    float getStep() const;

    void moveVertical(ControlMatrix *cm, float step);
    void moveHorizontal(ControlMatrix *cm, float step);
    void dropBomb(ControlMatrix *cm);


    void explosionAnimation(int bombX, int bombY);
    void destroyBomb(ControlMatrix *cm, int bombX, int bombY);


private:
    char playerNum;
    float x;
    float y;
    float step = 0.1;
    //float dHorizontal = 0;
    //float dVertical = 0;
    float xStart;
    float yStart;


};


#endif
