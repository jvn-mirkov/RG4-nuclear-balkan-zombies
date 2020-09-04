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
#define NEUTRAL (5)
#define UP (1)
#define DOWN (2)
#define LEFT (3)
#define RIGHT (4)


//global variables
int arrow1 = NEUTRAL;
int arrow2 = NEUTRAL;

//clipping planes
double clip_plane0[] = {1, 0, 0, 0};
double clip_plane1[] = {0, 0, 1, 0};
double clip_plane2[] = {-1, 0, 0, 15};
double clip_plane3[] = {0, 0, -1, 13.001};


// function declarations
static void on_keyboard(unsigned char key, int x, int y);

static void on_release(unsigned char, int, int);

static void on_reshape(int width, int height);

static void on_display(void);

static void ontimer(int value);

static void showDeathScreen();

void idle() { glutPostRedisplay(); }


// global objects
Player *player1 = new Player(1.5, 1.5, '1');
Player *player2 = new Player(11.5, 13.5, '2');

Map *map = new Map();
std::map<std::string, Box *> boxes;

ControlMatrix *cm = new ControlMatrix();

//std::list<Bomb> bombList = {};

Bomb *currentBomb1 = nullptr;
Bomb *currentBomb2 = nullptr;
bool death1 = false;
bool death2 = false;
unsigned int pozadina;

// funkcija preuzeta od druga RG141-tenkici uz njegovo odobrenje jer mi nije radilo ucitavanje tekstura sa image.cpp iz materijala
unsigned int tekstura(const char *putanja) {
    FILE *file = fopen(putanja, "rb");
    if (file == NULL) {
        std::cout << "greska";
        return 10000;
    }
    unsigned int sirina;
    unsigned int visina;
    unsigned short bit_c;
    unsigned int djubre;

    fread(&djubre, 2, 1, file);
    fread(&djubre, 4, 1, file);
    fread(&djubre, 2, 1, file);
    fread(&djubre, 2, 1, file);
    fread(&djubre, 4, 1, file);

    /* Ocitavaju se podaci drugog zaglavlja. */
    fread(&djubre, 4, 1, file);
    fread(&sirina, 4, 1, file);
    fread(&visina, 4, 1, file);
    fread(&djubre, 2, 1, file);
    fread(&bit_c, 2, 1, file);
    fread(&djubre, 4, 1, file);
    fread(&djubre, 4, 1, file);
    fread(&djubre, 4, 1, file);
    fread(&djubre, 4, 1, file);
    fread(&djubre, 4, 1, file);
    fread(&djubre, 4, 1, file);

    char *pixeli;
    unsigned char r, g, b, a;
    if (bit_c == 24)
        pixeli = (char *) malloc(3 * sirina * visina * sizeof(char));
    else if (bit_c == 32)
        pixeli = (char *) malloc(4 * sirina * visina * sizeof(char));
    else
        return 10001;
    if (bit_c == 24)
        for (int i = 0; i < sirina * visina; i++) {
            fread(&b, sizeof(char), 1, file);
            fread(&g, sizeof(char), 1, file);
            fread(&r, sizeof(char), 1, file);

            pixeli[3 * i] = g;
            pixeli[3 * i + 1] = b;
            pixeli[3 * i + 2] = r;
        }
    if (bit_c == 32)
        for (int i = 0; i < sirina * visina; i++) {
            fread(&b, sizeof(char), 1, file);
            fread(&g, sizeof(char), 1, file);
            fread(&r, sizeof(char), 1, file);
            fread(&a, sizeof(char), 1, file);

            pixeli[4 * i] = g;
            pixeli[4 * i + 1] = b;
            pixeli[4 * i + 2] = r;
            pixeli[4 * i + 3] = a;
        }
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 sirina, visina, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, pixeli);
    free(pixeli);
    fclose(file);
    glBindTexture(GL_TEXTURE_2D, 0);

    return id;
}

void setLighting() {

    GLfloat position[] = {15, 10, 0, 1};
    GLfloat ambient[] = {0.4, 0.4, 0.4, 1};
    GLfloat diffuse[] = {0.8, 0.8, 0.8, 1};
    GLfloat specular[] = {1, 1, 1, 1};


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
    glutInitWindowSize(1250, 750);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Nuclear Balkan Zombies");

    /* callback functions */
    glutKeyboardFunc(on_keyboard);
    glutKeyboardUpFunc(on_release);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    /* other */
    glClearColor(0.1, 0.1, 0.1, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    setLighting();

    glEnable(GL_TEXTURE_2D);
    pozadina = tekstura("novo.bmp");


    glEnable(GL_DEPTH_TEST);
    glLineWidth(1.25);

    //glutIdleFunc(idle);

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

static void on_release(unsigned char key, int x, int y) {

    switch (key) {

        case 's':
        case 'S':
            arrow1 = NEUTRAL;


            break;

        case 'w':
        case 'W':
            arrow1 = NEUTRAL;


            break;

        case 'a':
        case 'A':
            arrow1 = NEUTRAL;


            break;

        case 'd':
        case 'D':
            arrow1 = NEUTRAL;


            break;


        case 'i':
        case 'I':
            arrow2 = NEUTRAL;

            break;

        case 'k':
        case 'K':
            arrow2 = NEUTRAL;

            break;

        case 'j':
        case 'J':
            arrow2 = NEUTRAL;

            break;

        case 'l':
        case 'L':
            arrow2 = NEUTRAL;

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

        if (!currentBomb1) {
            player1->dropBomb(cm);
            currentBomb1 = new Bomb(player1->getX(), player1->getY()); //inlineuj dole
            //bombList.push_back(*b);
            std::cout << "player1 - drop bomb" << std::endl;
        }
    }

    if (value == TIMER_ID_B2) {

        if (!currentBomb2) {
            player2->dropBomb(cm);
            currentBomb2 = new Bomb(player2->getX(), player2->getY()); //inlineuj dole
            //bombList.push_back(*b);
            std::cout << "player2 - drop bomb" << std::endl;
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
            5, 15, 15,
            5, 0, 5,
            0, 1, 0
    );


    map->renderMap(pozadina);


    glClipPlane(GL_CLIP_PLANE0, clip_plane0);
    glClipPlane(GL_CLIP_PLANE1, clip_plane1);
    glClipPlane(GL_CLIP_PLANE2, clip_plane2);
    glClipPlane(GL_CLIP_PLANE3, clip_plane3);

    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);


    map->renderBoxes(cm);
    player1->renderPlayer();
    player2->renderPlayer();



    //provera da li je proslo dovoljno vremena za svaki deo animacije iscrtavanja unistavanja bombe
    // FIXME: izdvajanje oba uslova za obe bombe u funkciju ili u kolekcijsku petlju dovodi do nezeljenih efekata

    if (currentBomb1 != nullptr) {

        currentBomb1->Tick();

        if (100 > currentBomb1->getTime()) {
            map->renderBombAnimationPart1(currentBomb1->getX(), currentBomb1->getY());

        }


        if (50 > currentBomb1->getTime()) {
            map->renderBombAnimationPart2(currentBomb1->getX(), currentBomb1->getY());
        }

        if (0 == currentBomb1->getTime()) {
            currentBomb1->destroyBomb(cm, currentBomb1->getX(), currentBomb1->getY());
            //bombList.pop_front(); //proveri zasto nece erase
            death1 = player1->checkDeath(cm, currentBomb1->getX(), currentBomb1->getY());
            death2 = player2->checkDeath(cm, currentBomb1->getX(), currentBomb1->getY());
            currentBomb1 = nullptr;
        }

    }

    if (currentBomb2 != nullptr) {

        currentBomb2->Tick();

        if (100 > currentBomb2->getTime()) {
            map->renderBombAnimationPart1(currentBomb2->getX(), currentBomb2->getY());

        }


        if (50 > currentBomb2->getTime()) {
            map->renderBombAnimationPart2(currentBomb2->getX(), currentBomb2->getY());
        }

        if (0 == currentBomb2->getTime()) {
            currentBomb2->destroyBomb(cm, currentBomb2->getX(), currentBomb2->getY());
            //bombList.pop_front(); //proveri zasto nece erase
            death1 = player1->checkDeath(cm, currentBomb2->getX(), currentBomb2->getY());
            death2 = player2->checkDeath(cm, currentBomb2->getX(), currentBomb2->getY());
            currentBomb2 = nullptr;
        }

    }


    if (death1 || death2) {

        glutDisplayFunc(showDeathScreen);
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

//iscrtavanje teksta nakon sto neko izgubi
static void showDeathScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            5, 15, 15,
            5, 0, 5,
            0, 15, 0
    );


    char id = death1 ? '2' : '1';
    std::string c(1, id);

    std::string msg = "Pobedio je igrac " + c + ", pritisni ESC ";

    glDisable(GL_LIGHTING);
    glColor3f(1, 1, 1);
    glRasterPos3f(3, 5, 3);
    for (int i = 0; i < msg.length() - 1; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg[i]);


    glutSwapBuffers();

}