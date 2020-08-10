#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<vector>
#include "unistd.h"
#include <chrono>
#include <thread>
#include "ControlMatrix.h"
#include "Player.h"


Player::Player(float xStart, float yStart, char playerNum) : xStart(xStart), yStart(yStart), playerNum(playerNum) {
    this->x = xStart;
    this->y = yStart;
    this->playerNum = playerNum;
}

void Player::renderPlayer() {

    glPushMatrix();

    glColor3f(0, 0, 0);
    glTranslatef(this->y, 0.5, this->x);


    glScalef(1, 1, 1);
    glutSolidSphere(0.4, 10, 10);

    glPopMatrix();


    //this->setX(dHorizontal + xStart);
    //this->setY(dVertical + yStart);
    std::cout << "Player:" << this->x << "/" << this->y << std::endl;


}


void Player::moveVertical(ControlMatrix *cm, float step) {

    int stepSign = step >= 0 ? 1:-1;

    int X = static_cast<int>(trunc(this->x ));
    int oldY = static_cast<int>(trunc(this->y ));
    int futureY = static_cast<int>(trunc((this->y+step+stepSign*0.3) ));


    if('0' == cm->mx[X][futureY] || this->playerNum == cm->mx[X][futureY]){

        if(oldY != futureY) {
            cm->mx[X][oldY] = '0';
            cm->mx[X][futureY] = this->playerNum;
        }

        this->y += step;
    }


}

void Player::moveHorizontal(ControlMatrix *cm, float step) {

    int stepSign = step >= 0 ? 1:-1;

    int oldX = static_cast<int>(trunc(this->x));
    int futureX = static_cast<int>(trunc((this->x+step+stepSign*0.3) ));
    int Y = static_cast<int>(trunc(this->y ));



    if('0' == cm->mx[futureX][Y] || this->playerNum == cm->mx[futureX][Y]){

        if(oldX != futureX) {
            cm->mx[oldX][Y] = '0';
            cm->mx[futureX][Y] = this->playerNum;
        }



        this->x += step;
    }


}


void Player::dropBomb(ControlMatrix *cm) {


    int bombX = static_cast<int>(trunc(this->x ));
    int bombY = static_cast<int>(trunc(this->y ));

    std::cout << "--------" << std::endl;
    std::cout << "Drop on" << bombX << "/" << bombY << std::endl;

    if ('Z' != cm->mx[bombX][bombY] && 'B' != cm->mx[bombX][bombY])
        cm->mx[bombX][bombY] = 'Q';


    destroyBomb(cm, bombX, bombY);
    //std::thread bombThread(&Player::destroyBomb, cm, bombX,bombY);
    //bombThread.join();

}


void Player::explosionAnimation(int bombX, int bombY) {

    sleep(2000);

//TODO: smanji kod tako sto ce se iterirati kroz niz vektora kao parametri za glTranslate
    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(1, 0, 0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(-1, 0, 0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(0, 0, 1);
    glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(0, 0, -1);
    glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    std::cout << "Nacrtano prvo" << std::endl;

    sleep(1000);
    std::cout << "prvo sleep" << std::endl;

    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(2, 0, 0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(-2, 0, 0);
    glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(0, 0, 2);
    glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(0, 0, -2);
    glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    std::cout << "Nacrtano drugo" << std::endl;


    sleep(1000);
    std::cout << "drugo sleep" << std::endl;
}


void Player::destroyBomb(ControlMatrix *cm, int bombX, int bombY) {

    //this->explosionAnimation(bombX, bombY);


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


void Player::setX(float x) {
    this->x = x;
}

void Player::setY(float y) {
    this->y = y;
}

float Player::getStep() const {
    return step;
}



