#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>


// opengl libs
#include <GL/glut.h>
#include <GL/gl.h>


// .h files
#include "Player.h"
#include "Map.h"
#include "Box.h"
#include "ControlMatrix.h"
#include "Bomb.h"

//definovi:
#define TIMER_ID_P1 (0)
#define TIMER_ID_P2 (6)
#define TIMER_INTERVAL (10)
#define DEFAULT (5)
#define UP (1)
#define DOWN (2)
#define LEFT (3)
#define RIGHT (4)


//global variables
float p1updown, p1leftright = 0;
float p2updown, p2leftright = 0;
int arrow = DEFAULT;


// function declarations
static void on_keyboard(unsigned char key, int x, int y);

static void on_reshape(int width, int height);

static void on_display(void);

static void ontimer(int value);


// global objects
Player *player1 = new Player(1.5, 1.5);
Map *map = new Map();
std::map<std::string, Box *> boxes;

void showBoxesMap() {

    for (auto e : boxes) {
        std::cout << e.first << " -> " << e.second << std::endl;
    }

}


void initBoxes() {

    ControlMatrix *cm = new ControlMatrix();

    //cm->showMatrix();


    for (int i = 14; i >= 0; i--) {
        for (int j = 12; j >= 0; j--) {
            if (cm->mx[j][i] == 'B') {
                std::string s;

                std::cout << j << "/"<< i << std::endl;


                s += std::to_string(j);
                s += std::to_string(i);

                std::cout << s << std::endl;

                boxes[s] = new Box(j, i);

            }
        }

    }
}


int main(int argc, char **argv) {

    /* initialize glut */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* initialize window */
    glutInitWindowSize(750, 750); //1920x1080
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Nuclear Balkan Zombies");

    /* callback functions */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* other */
    glClearColor(0.1, 0.1, 0.1, 0);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1.25);


    initBoxes();
    showBoxesMap();


    glutMainLoop();

    return 0;

}

static void on_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(EXIT_SUCCESS);
            break;


        case 's':
        case 'S':
        case GLUT_KEY_UP:
            arrow = DOWN;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P1);

            break;

        case 'w':
        case 'W':
            arrow = UP;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P1);

            break;

        case 'a':
        case 'A':
            arrow = LEFT;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P1);

            break;

        case 'd':
        case 'D':
            arrow = RIGHT;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P1);

            break;

        case 'i':
        case 'I':
            arrow = UP;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P2);
            break;

        case 'k':
        case 'K':
            arrow = DOWN;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P2);
            break;

        case 'j':
        case 'J':
            arrow = LEFT;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P2);
            break;

        case 'l':
        case 'L':
            arrow = RIGHT;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P2);
            break;

    }
}

static void ontimer(int value) {


    if (value == TIMER_ID_P1) {

        if (arrow == RIGHT) {
            player1->moveVertical(player1->getStep());

        } else if (arrow == UP) {
            player1->moveHorizontal(-player1->getStep());

        } else if (arrow == LEFT) {
            player1->moveVertical(-player1->getStep());

        } else if (arrow == DOWN) {
            player1->moveHorizontal(player1->getStep());

        }

    }

    if (value == TIMER_ID_P2) {

        if (arrow == DOWN) {
            p2updown = p2updown + 0.5;

        } else if (arrow == LEFT) {
            p2leftright = p2leftright - 0.5;

        } else if (arrow == UP) {
            p2updown = p2updown - 0.5;

        } else if (arrow == RIGHT) {
            p2leftright = p2leftright + 0.5;

        }

    }


    glutPostRedisplay();


}

static void on_display(void) {


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            5, 15, 20,
            5, 0, 5,
            0, 11, 0
    );


    map->renderMap();
    map->renderBoxes();
    player1->renderPlayer();


/*
    glPushMatrix();

    glColor3f(0, 0, 0);
    glTranslatef(p2updown + 1.5, 1 - 0.5, p2leftright + 1.5);

    glScalef(1, 1, 1);
    glutSolidSphere(0.4, 10, 10);

    glPopMatrix();




    glPushMatrix();

    glColor3f(0, 0, 0);
    glTranslatef(p1leftright + 3, 1 - 0.50, p1updown + 3);

    glScalef(1, 1, 1);
    glutSolidSphere(0.4, 10, 10);

    glPopMatrix();

*/


    glBegin(GL_LINES);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(50, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 50, 0);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 50);

    glEnd();


    glutSwapBuffers();

}

static void on_reshape(int width, int height) {

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 100);
}

