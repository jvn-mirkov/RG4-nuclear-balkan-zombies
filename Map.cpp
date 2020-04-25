#include "Map.h"
#include "ControlMatrix.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>

Map::Map() {}

void Map::renderMap() {


    glPushMatrix();

    glColor3f(0.556863, 0.137255, 0.137255);
    glTranslatef(7.5, -0.5, 6.5); /*pod*/



    glScalef(15, 1, 13);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.36, 0.25, 0.26);
    glTranslatef(7.5, 0.50, 0.5); /*zid1*/




    glScalef(15, 1, 1);
    glutSolidCube(1);

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.36, 0.25, 0.26);
    glTranslatef(7.5, 1 - 0.50, 0.5 + 12); /*zid2*/



    glScalef(15, 1, 1);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.36, 0.25, 0.26);
    glTranslatef(0 + 0.5, 1 - 0.5, 6.5); /*zid3*/





    glScalef(1, 1, 13);
    glutSolidCube(1);

    glPopMatrix();


    glPushMatrix();

    glColor3f(0.36, 0.25, 0.26);
    glTranslatef(14 + 0.5, 1 - 0.5, 6.5); /*zid4*/





    glScalef(1, 1, 13);
    glutSolidCube(1);

    glPopMatrix();


/*STUBOVI*/
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

void Map::renderBoxes() {

    ControlMatrix *cm = new ControlMatrix();

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

void Map::renderBombs() {}
