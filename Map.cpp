#include "Map.h"
#include "ControlMatrix.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>


#define POS 40

Map::Map() {}

//postavka poda, zidova i stubova
void Map::renderMap(unsigned int pozadina) {


    glDisable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, pozadina);

    glPushMatrix();


    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-(POS), -5, -(POS));
    glTexCoord2f(0, 0);
    glVertex3f(-POS, -5, POS);
    glTexCoord2f(1, 0);
    glVertex3f(POS, -5, POS);
    glTexCoord2f(1, 1);
    glVertex3f(POS, -5, -POS);
    glEnd();

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_LIGHTING);




    //pod
    GLfloat specularPod[] = {0.5, 0.5, 0.5, 0.5};
    GLfloat ambientPod[] = {0.1, 0.1, 0.1};
    GLfloat diffusePod[] = {0.690, 0.769, 0.871};
    int shininess = 100;


    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientPod);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffusePod);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularPod);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


    glPushMatrix();

    //glColor3f(0.556863, 0.137255, 0.137255);
    glTranslatef(7.5, -0.5, 6.5);


    glScalef(15, 1, 13);
    glutSolidCube(1);

    glPopMatrix();




    //zidovi

    GLfloat specularZid[] = {0.5, 0.5, 0.5, 0.5};
    GLfloat ambientZid[] = {0.1, 0.1, 0.1};
    GLfloat diffuseZid[] = {0.184, 0.310, 0.31};


    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientZid);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseZid);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularZid);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


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



    GLfloat specularStub[] = {0.5, 0.5, 0.5, 0.5};
    GLfloat ambientStub[] = {0.1, 0.1, 0.1};
    GLfloat diffuseStub[] = {0.184, 0.310, 0.31};


    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientStub);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseStub);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularStub);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);


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



    GLfloat specularBox[] = {1, 1, 1, 1};
    GLfloat ambientBox[] = {0.3, 0.1, 0.1};
    GLfloat diffuseBox[] = {0.3, 0.2, 0.2};


    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientBox);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseBox);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularBox);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);


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

    GLfloat specularBomb[] = {0.1, 0.1, 0.1, 0.1};
    GLfloat ambientBomb[] = {0.1, 0.1, 0.1};
    GLfloat diffuseBomb[] = {0.8, 0.1, 0.1};


    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientBomb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseBomb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularBomb);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);


    for (int i = 15 - 1; i >= 0; i--) {
        for (int j = 13 - 1; j >= 0; j--) {
            if (cm->bx[j][i] == 'Q') {

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

    GLfloat specularA1[] = {0.1, 0.1, 0.1, 0.1};
    GLfloat ambientA1[] = {0.3, 0.1, 0.1};
    GLfloat diffuseA1[] = {0.8, 0.1, 0.1};


    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientA1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseA1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularA1);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);


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

    GLfloat specularA1[] = {0.1, 0.1, 0.1, 0.1};
    GLfloat ambientA1[] = {0.3, 0.1, 0.1};
    GLfloat diffuseA1[] = {1.0, 0.1, 0.1};


    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientA1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseA1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularA1);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);


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









