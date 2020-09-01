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



    //std::cout << "Player:" << this->x << "/" << this->y << std::endl;


}


void Player::moveVertical(ControlMatrix *cm, float step) {

    int stepSign = step >= 0 ? 1:-1;

    int X = static_cast<int>(trunc(this->x ));
    int oldY = static_cast<int>(trunc(this->y ));
    int futureY = static_cast<int>(trunc((this->y+step+stepSign*0.3) ));


    if( 'Q' == cm->mx[X][futureY] || '0' == cm->mx[X][futureY] || this->playerNum == cm->mx[X][futureY]){

        if(oldY != futureY && 'Q' != cm->mx[X][futureY]) {
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



    if('Q' == cm->mx[futureX][Y] || '0' == cm->mx[futureX][Y] || this->playerNum == cm->mx[futureX][Y]){

        if(oldX != futureX && 'Q' == cm->mx[futureX][Y]) {
            cm->mx[oldX][Y] = '0';
            cm->mx[futureX][Y] = this->playerNum;
        }



        this->x += step;
    }


}

//updateuje kontrolnu matricu informacijom gde je bomba postavljena, postavlja se na trenutne koordinate playera(mapirano na odredjenu poziciju u matrici)
void Player::dropBomb(ControlMatrix *cm) {


    int bombX = static_cast<int>(trunc(this->x ));
    int bombY = static_cast<int>(trunc(this->y ));

    std::cout << "--------" << std::endl;
    std::cout << "Drop on" << bombX << "/" << bombY << std::endl;

    if ('Z' != cm->mx[bombX][bombY] && 'B' != cm->mx[bombX][bombY])
        cm->mx[bombX][bombY] = 'Q'; //problem jer ga player uvek pregazi/ mora paralelna mapa...





}

//provera da li je u toku eksplozije player bio u njenom opsegu, ako jeste, izgubio je
void Player::checkDeath(ControlMatrix *cm, float bombX, float bombY){

    int bombXt = static_cast<int>(trunc(bombX ));
    int bombYt = static_cast<int>(trunc(bombY ));

    if (cm->mx[bombXt][bombYt] == playerNum) { showDeathScreen(); }
    else if (cm->mx[bombXt - 1][bombYt] == playerNum) { showDeathScreen(); }
    else if (cm->mx[bombXt - 2][bombYt] == playerNum) { showDeathScreen(); }
    else if (cm->mx[bombXt + 1][bombYt] == playerNum) { showDeathScreen(); }
    else if (cm->mx[bombXt + 2][bombYt] == playerNum) { showDeathScreen(); }
    else if (cm->mx[bombXt][bombYt - 1] == playerNum) { showDeathScreen(); }
    else if (cm->mx[bombXt][bombYt - 2] == playerNum) { showDeathScreen(); }
    else if (cm->mx[bombXt][bombYt + 1] == playerNum) { showDeathScreen(); }
    else if (cm->mx[bombXt][bombYt + 2] == playerNum) { showDeathScreen(); }




}


void Player::showDeathScreen(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            5, 15, 15,
            5, 0, 5,
            0, 15, 0
    );


    std::cout << "uslo";
    std::string c(1,this->playerNum);

    std::string msg = "Pobedio je igrac " + c + ", pritisni ESC ";

    glColor3f(1, 1, 1); // ???nece??
    glRasterPos3f(3, 5, 3);
    for (int i=0; i < msg.length()-1; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg[i]);







    glutSwapBuffers();

    getchar();

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

float Player::getX() const {
    return x;
}

float Player::getY() const {
    return y;
}

