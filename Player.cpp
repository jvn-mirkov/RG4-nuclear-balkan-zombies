#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<vector>
#include "unistd.h"
#include <chrono>
#include <thread>
#include "ControlMatrix.h"
#include "Player.h"



Player::Player(float xStart, float yStart) : xStart(xStart), yStart(yStart) {
    this->x = xStart;
    this->y = yStart;
}

void Player::renderPlayer() {

    glPushMatrix();

    glColor3f(0, 0, 0);
    glTranslatef(dVertical + yStart, 0.5, dHorizontal + xStart);



    glScalef(1, 1, 1);
    glutSolidSphere(0.4, 10, 10);

    glPopMatrix();


    this->setX(dHorizontal + xStart);
    this->setY(dVertical + yStart);
    std::cout << "Player:" << this->x << "/" << this->y << std::endl;



}


void Player::moveVertical(float step){
    this->y += step;
    this->dVertical += step;
    std::cout << "moveVertical "<< step << std::endl;
}
void Player::moveHorizontal(float step){
    this->x += step;
    this->dHorizontal += step;
    std::cout << "moveHorizontal "<< step << std::endl;
}


void Player::dropBomb(ControlMatrix *cm){


    int bombX = static_cast<int>(floor(this->x));
    int bombY = static_cast<int>(floor(this->y));


    cm->mx[bombX][bombY] = 'Q';


    destroyBomb(cm, bombX,bombY);
    //std::thread bombThread(&Player::destroyBomb, cm, bombX,bombY);
    //bombThread.join();

}





void Player::explosionAnimation(int bombX, int bombY){

    sleep(2000);

//TODO: smanji kod tako sto ce se iterirati kroz niz vektora kao parametri za glTranslate
    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(1,0,0);
    glRotatef(45,0.0,0.0,1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();



    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(-1,0,0);
    glRotatef(45,0.0,0.0,1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();



    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(0,0,1);
    glRotatef(45,0.0,0.0,1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();




    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(0,0,-1);
    glRotatef(45,0.0,0.0,1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    std::cout << "Nacrtano prvo"<< std::endl;

    sleep(1000);
    std::cout << "prvo sleep"<< std::endl;

    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(2,0,0);
    glRotatef(45,0.0,0.0,1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();



    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(-2,0,0);
    glRotatef(45,0.0,0.0,1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();



    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(0,0,2);
    glRotatef(45,0.0,0.0,1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();




    glPushMatrix();

    glColor3f(0.6, 0.4, 0.76);
    glTranslatef(0,0,-2);
    glRotatef(45,0.0,0.0,1.0);
    glScalef(0.45, 0.45, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    std::cout << "Nacrtano drugo"<< std::endl;


    sleep(1000);
    std::cout << "drugo sleep"<< std::endl;
}


void Player::destroyBomb(ControlMatrix *cm, int bombX, int bombY){

    this->explosionAnimation(bombX, bombY);


    cm->mx[bombX][bombY] = '0';



    if(bombX == 1){
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        //if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    }
    if(bombY == 1){
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        //if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    }
    if(bombX == 13){
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        //if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    }
    if(bombY == 11){
        if (cm->mx[bombX - 1][bombY] == 'B') { cm->mx[bombX - 1][bombY] = '0'; }
        if (cm->mx[bombX - 2][bombY] == 'B') { cm->mx[bombX - 2][bombY] = '0'; }
        if (cm->mx[bombX + 1][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX + 2][bombY] == 'B') { cm->mx[bombX + 2][bombY] = '0'; }
        if (cm->mx[bombX][bombY - 1] == 'B') { cm->mx[bombX][bombY - 1] = '0'; }
        if (cm->mx[bombX][bombY - 2] == 'B') { cm->mx[bombX][bombY - 2] = '0'; }
        if (cm->mx[bombX][bombY + 1] == 'B') { cm->mx[bombX][bombY + 1] = '0'; }
        //if (cm->mx[bombX][bombY + 2] == 'B') { cm->mx[bombX][bombY + 2] = '0'; }
    }


    else
    {
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



