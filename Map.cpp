#include "Map.h"
#include "ControlMatrix.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

Map::Map() {}

//postavka poda, zidova i stubova
void Map::renderMap() {


    //pod
    glPushMatrix();

    glColor3f(0.556863, 0.137255, 0.137255);
    glTranslatef(7.5, -0.5, 6.5);


    glScalef(15, 1, 13);
    glutSolidCube(1);

    glPopMatrix();



    //zidovi

    glPushMatrix();

    glColor3f(0.36, 0.25, 0.26);
    glTranslatef(7.5, 0.50, 0.5);


    glScalef(15, 1, 1);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.36, 0.25, 0.26);
    glTranslatef(7.5, 1 - 0.50, 0.5 + 12);


    glScalef(15, 1, 1);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.36, 0.25, 0.26);
    glTranslatef(0 + 0.5, 1 - 0.5, 6.5);


    glScalef(1, 1, 13);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.36, 0.25, 0.26);
    glTranslatef(14 + 0.5, 1 - 0.5, 6.5);


    glScalef(1, 1, 13);
    glutSolidCube(1);

    glPopMatrix();


    //stubovi
    int i, j;
    for (j = 0; j < 11; j = j + 2) {
        for (i = 0; i < 13; i = i + 2) {
            glPushMatrix();

            glColor3f(0.36, 0.25, 0.26);
            glTranslatef(i + 2 + 0.5, 1 - 0.5, j + 2.5);

            glScalef(1, 1, 1);
            glutSolidCube(1);

            glPopMatrix();

        }
    }

    glPushMatrix();


}

//cita kontrolnu matricu i prema njoj iscrtava kutije
void Map::renderBoxes(ControlMatrix *cm) {

    //ControlMatrix *cm = new ControlMatrix();

    //cm->showMatrix();

    for (int i = 15 - 1; i >= 0; i--) {
        for (int j = 13 - 1; j >= 0; j--) {
            if (cm->mx[j][i] == 'B') {

                glPushMatrix();

                glColor3f(0.1, 0.1, 0.1);
                glTranslatef(i + 0.5, 1 - 0.5, j + 0.5);


                glScalef(1, 1, 1);
                glutSolidCube(1);

                glPopMatrix();


            }
        }

    }

}

//cita kontrolnu matricu i prema njoj iscrtava bombe
void Map::renderBombs(ControlMatrix *cm) {

    for (int i = 15 - 1; i >= 0; i--) {
        for (int j = 13 - 1; j >= 0; j--) {
            if (cm->mx[j][i] == 'Q') {

                glPushMatrix();

                glColor3f(0.7, 0.1, 0.7);


                glTranslatef(i + 0.5, 1 - 0.5, j + 0.5);

                glRotatef(45, 0.0, 0.0, 1.0);
                glScalef(0.45, 0.45, 0.45);
                glutSolidCube(1);

                glPopMatrix();


            }
        }

    }


}

//iscrtavanje eksplozije za po jedno polje horizontalno i vertikalno u oba smera u odnosu na prosledjene kordinate
void Map::renderBombAnimationPart1(float x, float y) {
    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(1 + y, 0 + 2, 0 + x);
    //glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 2, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(-1 + y, 0 + 2, 0 + x);
    //glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 2, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(0 + y, 0 + 2, 1 + x);
    //glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 2, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(0 + y, 0 + 2, -1 + x);
    //glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 2, 0.45);
    glutSolidCube(1);

    glPopMatrix();


}

//iscrtavanje eksplozije za po dva polja horizontalno i vertikalno u oba smera u odnosu na prosledjene kordinate
void Map::renderBombAnimationPart2(float x, float y) {

    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(2 + y, 0 + 2, 0 + x);
    //glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 2, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(-2 + y, 0 + 2, 0 + x);
    //glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 2, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(0 + y, 0 + 2, 2 + x);
    //glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 2, 0.45);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(1, 0, 0);
    glTranslatef(0 + y, 0 + 2, -2 + x);
    //glRotatef(45, 0.0, 0.0, 1.0);
    glScalef(0.45, 2, 0.45);
    glutSolidCube(1);

    glPopMatrix();


}














