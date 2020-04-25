#include<GL/gl.h>
#include<GL/glut.h>
#include<iostream>
#include<vector>

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




void Player::setX(float x) {
    this->x = x;
}

void Player::setY(float y) {
    this->y = y;
}

float Player::getStep() const {
    return step;
}



