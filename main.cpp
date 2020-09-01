#include <iostream>
#include <map>
#include <list>

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
#define TIMER_ID_B1 (11)
#define TIMER_ID_B2 (12)
#define TIMER_INTERVAL (10)
#define TIMER_INTERVAL2 (13)
#define DEFAULT (5)
#define UP (1)
#define DOWN (2)
#define LEFT (3)
#define RIGHT (4)


//global variables
int arrow1 = DEFAULT;
int arrow2 = DEFAULT;

//clipping planes
double clip_plane0[] = {1, 0, 0, 0};
double clip_plane1[] = {0, 0, 1, 0};
double clip_plane2[] = {-1, 0, 0, 15};
double clip_plane3[] = {0, 0, -1, 13.001};


// function declarations
static void on_keyboard(unsigned char key, int x, int y);

static void on_reshape(int width, int height);

static void on_display(void);

static void ontimer(int value);

void idle(){    glutPostRedisplay();}


// global objects
Player *player1 = new Player(1.5, 1.5, '1');
Player *player2 = new Player(11.5, 13.5, '2');
Map *map = new Map();
std::map<std::string, Box *> boxes;
ControlMatrix *cm = new ControlMatrix();
//std::list<Bomb> bombList = {};
Bomb *currentBomb1 = nullptr;
Bomb *currentBomb2 = nullptr;

//int globalint = 0;

void showBoxesMap() {

    for (auto e : boxes) {
        std::cout << e.first << " -> " << e.second << std::endl;
    }

}

void showBombsMap() {


    if (currentBomb1 != nullptr)
        std::cout << "######" << std::endl;
    std::cout << currentBomb1->getX() << "/" << currentBomb1->getY() << "/" << currentBomb1->getTime() << std::endl;
    std::cout << "######" << std::endl;

}

/*
void initBoxes() {



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
*/
void setLighting() {
    //odredjujemo vektore
    GLfloat position[] = {10, 10, 10, 1};
    GLfloat ambient[] = {0.4, 0.4, 0.4, 1};
    GLfloat diffuse[] = {0.8, 0.8, 0.8, 1};
    GLfloat specular[] = {1, 1, 1, 1};

    //inicijalizujemo osobine osvetljenja
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
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
    glutIdleFunc(idle);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //setLighting();

    //initBoxes();
    //showBoxesMap();


    glutMainLoop();

    return 0;

}

static void on_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(EXIT_SUCCESS);



        case 'm':
        case 'M':
            cm->showMatrix();
            break;

        case 'x':
        case 'X':
            showBombsMap();
            break;

        case 's':
        case 'S':
            arrow1 = DOWN;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P1);

            break;

        case 'w':
        case 'W':
            arrow1 = UP;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P1);

            break;

        case 'a':
        case 'A':
            arrow1 = LEFT;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P1);

            break;

        case 'd':
        case 'D':
            arrow1 = RIGHT;
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_P1);

            break;

        case 'q':
        case 'Q':
            glutTimerFunc(TIMER_INTERVAL, ontimer, TIMER_ID_B1);

            break;


        case 'i':
        case 'I':
            arrow2 = UP;
            glutTimerFunc(TIMER_INTERVAL2, ontimer, TIMER_ID_P2);
            break;

        case 'k':
        case 'K':
            arrow2 = DOWN;
            glutTimerFunc(TIMER_INTERVAL2, ontimer, TIMER_ID_P2);
            break;

        case 'j':
        case 'J':
            arrow2 = LEFT;
            glutTimerFunc(TIMER_INTERVAL2, ontimer, TIMER_ID_P2);
            break;

        case 'l':
        case 'L':
            arrow2 = RIGHT;
            glutTimerFunc(TIMER_INTERVAL2, ontimer, TIMER_ID_P2);
            break;


        case 'u':
        case 'U':
            glutTimerFunc(TIMER_INTERVAL2, ontimer, TIMER_ID_B2);

            break;


    }
    glutPostRedisplay();
}

static void ontimer(int value) {


    if (value == TIMER_ID_P1) {

        if (arrow1 == RIGHT) {
            player1->moveVertical(cm, player1->getStep());

        } else if (arrow1 == UP) {
            player1->moveHorizontal(cm, -player1->getStep());

        } else if (arrow1 == LEFT) {
            player1->moveVertical(cm, -player1->getStep());

        } else if (arrow1 == DOWN) {
            player1->moveHorizontal(cm, player1->getStep());

        }

    }

    if (value == TIMER_ID_P2) {

        if (arrow2 == RIGHT) {
            player2->moveVertical(cm, player2->getStep());

        } else if (arrow2 == UP) {
            player2->moveHorizontal(cm, -player2->getStep());

        } else if (arrow2 == LEFT) {
            player2->moveVertical(cm, -player2->getStep());

        } else if (arrow2 == DOWN) {
            player2->moveHorizontal(cm, player2->getStep());

        }

    }

    if (value == TIMER_ID_B1) {

        player1->dropBomb(cm);
        currentBomb1 = new Bomb(player1->getX(), player1->getY()); //inlineuj dole
        //bombList.push_back(*b);
        std::cout << "player1 - drop bomb" << std::endl;
    }

    if (value == TIMER_ID_B2) {

        player2->dropBomb(cm);
        currentBomb2 = new Bomb(player2->getX(), player2->getY()); //inlineuj dole
        //bombList.push_back(*b);
        std::cout << "player2 - drop bomb" << std::endl;
    }
    glutPostRedisplay();


}

static void on_display(void) {


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            5, 15, 15,
            5, 0, 5,
            0, 15, 0
    );


    glClipPlane(GL_CLIP_PLANE0, clip_plane0);
    glClipPlane(GL_CLIP_PLANE1, clip_plane1);
    glClipPlane(GL_CLIP_PLANE2, clip_plane2);
    glClipPlane(GL_CLIP_PLANE3, clip_plane3);

    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);

    //globalint++;
    //std::cout << globalint<< std::endl;


    map->renderMap();
    map->renderBoxes(cm);
    player1->renderPlayer();
    player2->renderPlayer();



    //provera da li je proslo dovoljno vremena za svaki deo animacije iscrtavanja unistavanja bombe
    // FIXME: izdvajanje oba uslova za obe bombe u funkciju ili u kolekcijsku petlju dovodi do nezeljenih efekata
    if (currentBomb1 != nullptr) {

        currentBomb1->Tick();

        if (200 > currentBomb1->getTime()) {
            std::cout << "40" << std::endl;
            map->renderBombAnimationPart1(currentBomb1->getX(), currentBomb1->getY());

        }


        if (100 > currentBomb1->getTime()) {
            std::cout << "20" << std::endl;
            map->renderBombAnimationPart2(currentBomb1->getX(), currentBomb1->getY());
        }

        if (0 == currentBomb1->getTime()) {
            std::cout << "detonate" << std::endl;
            currentBomb1->destroyBomb(cm, currentBomb1->getX(), currentBomb1->getY());
            //bombList.pop_front(); //proveri zasto nece erase
            player1->checkDeath(cm, currentBomb1->getX(), currentBomb1->getY());
            player2->checkDeath(cm, currentBomb1->getX(), currentBomb1->getY());
            currentBomb1 = nullptr;
        }

    }

    if (currentBomb2 != nullptr) {

        currentBomb2->Tick();

        if (200 > currentBomb2->getTime()) {
            std::cout << "40" << std::endl;
            map->renderBombAnimationPart1(currentBomb2->getX(), currentBomb2->getY());

        }


        if (100 > currentBomb2->getTime()) {
            std::cout << "20" << std::endl;
            map->renderBombAnimationPart2(currentBomb2->getX(), currentBomb2->getY());
        }

        if (0 == currentBomb2->getTime()) {
            std::cout << "detonate" << std::endl;
            currentBomb2->destroyBomb(cm, currentBomb2->getX(), currentBomb2->getY());
            //bombList.pop_front(); //proveri zasto nece erase
            player1->checkDeath(cm, currentBomb2->getX(), currentBomb2->getY());
            player2->checkDeath(cm, currentBomb2->getX(), currentBomb2->getY());
            currentBomb2 = nullptr;
        }

    }

    map->renderBombs(cm);


    glDisable(GL_CLIP_PLANE3);
    glDisable(GL_CLIP_PLANE2);
    glDisable(GL_CLIP_PLANE1);
    glDisable(GL_CLIP_PLANE0);







    glutSwapBuffers();


    glutPostRedisplay();
    glFlush();

}

static void on_reshape(int width, int height) {

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 100);
}

