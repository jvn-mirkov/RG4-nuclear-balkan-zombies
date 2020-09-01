#include "Bomb.h"
#include "ControlMatrix.h"
#include <GL/glut.h>
#include <GL/gl.h>


Bomb::Bomb(float x, float y) : x(x), y(y) {
    this->x = x;
    this->y = y;
    this->time = 1800;
}

Bomb::~Bomb() {

}

//dekrementacija brojaca koji utice na animaciju bombe i  njeno trajanje
void Bomb::Tick() {

    this->time--;

}


int Bomb::getTime() const {
    return time;
}

float Bomb::getX() const {
    return x;
}

float Bomb::getY() const {
    return y;
}

//sklanja sa kontrolne matrice sve kutije koje su uhvacene animacijom aktiviranja bombe i brise trenutnu bombu
void Bomb::destroyBomb(ControlMatrix *cm, int bombX, int bombY) {


    cm->mx[bombX][bombY] = '0';


    if (bombX == 1) {
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        //if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    }
    if (bombY == 1) {
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        //if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    }
    if (bombX == 13) {
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        //if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    }
    if (bombY == 11) {
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        //if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    } else {
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    }


}
