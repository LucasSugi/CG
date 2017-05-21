#include "alien.h"
#include "bullet.h"
#include "manager.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

//Define the size of alien's file
#define ROW 8
#define COL 8

//This two variable is used to set the initial position of first alien
//The variable cause one displacement in LEFT and TOP coordinates
float INC_X = 0.1;
float INC_Y = 0.1;

//This variable defines how many aliens have per line
int AMOUNT_ALIEN_ROW;

//This defines how lines of aliens have space invaders
int LINES_ALIEN = 5;

//This variable define how long is the movement of one alien in horizontal
int TIME_MOVE_ALIEN = 1000;

//This variable define time for one shoot
int TIME_SHOOT_ALIEN = 3;

//This variable defines the number of movement until one alien go down
int TIME_MOVE_DOWN = 20;

//This variable defines the amount of jump in horizontal and vertical
float JUMP = 0.1;

//This variable MUST BE the same values of parameters in gluOrtho2D
int LEFT, RIGHT, BOTTOM, TOP;

//This variable defines the accumulated amount of jump in horizontal and vertical
float JUMP_X, JUMP_Y = 0;

//This variable will be used for check where the alien need to move
bool LEFT_RIGHT;
bool BOTTOM_TOP;

//RGB color for alien
float R = 0.0f, G = 1.0f, B = 0.0f;

//This variable define size of point that will be used for draw one alien
float POINT_SIZE = 2.0f;

typedef struct alien {
    float xAlien, yAlien;
    bool live;
    char type;
} ALIEN;

typedef struct control_alien {
    int** shape1;
    int** shape2;
    int** shape3;
    vector<ALIEN*>* vec;
} CONTROL_ALIEN;

CONTROL_ALIEN* alien;

/*
 * Change the dificulty of game
 */
void changeDificulty(int time_move_alien, int time_shoot_alien)
{
    if (time_move_alien != -1)
        TIME_MOVE_ALIEN = time_move_alien;
    if (time_shoot_alien != -1)
        TIME_SHOOT_ALIEN = time_shoot_alien;
}

/*
 * Read content of alien's file
 */
int** readFile(const char* filename)
{

    int c;
    FILE* fp;
    int** shape;

    //read the shape of alien1
    fp = fopen(filename, "r");

    if (fp == NULL)
        return NULL;

    //create matrix
    shape = (int**)malloc(sizeof(int*) * ROW);

    //It's necessary that file have 8 rows and cols
    for (int i = 0; i < ROW; i++) {
        shape[i] = (int*)malloc(sizeof(int) * COL);
        for (int j = 0; j < COL; j++) {
            c = fgetc(fp);
            shape[i][j] = c - 48;
        }
        //ignore breakline
        c = fgetc(fp);
    }

    //close file
    fclose(fp);

    return shape;
}

/*
 * Initializa one struct that is responsible to control aliens
 */
void createAlien(float left, float right, float bottom, float top, float xV, float yV, float Sx, float Sy, int nAlien)
{
    int i;
    ALIEN* al;

    //Create struct
    alien = (CONTROL_ALIEN*)malloc(sizeof(CONTROL_ALIEN));

    //initialize some variable
    LEFT = left;
    RIGHT = right;
    BOTTOM = bottom;
    TOP = top;

    LEFT_RIGHT = false;
    BOTTOM_TOP = false;

    JUMP_X = JUMP_Y = 0;

    AMOUNT_ALIEN_ROW = nAlien;

    //read from one file the shape of aliens
    alien->shape1 = readFile("alien1");
    alien->shape2 = readFile("alien2");
    alien->shape3 = readFile("alien3");

    alien->vec = new vector<ALIEN*>;

    //initial position of the first alien
    top = top - INC_Y;
    left = left + INC_X;

    //row 1
    for (i = 0; i < AMOUNT_ALIEN_ROW; i++) {
        al = (ALIEN*)malloc(sizeof(ALIEN));
        al->live = true;
        al->type = '1';
        al->xAlien = left + i * JUMP;
        al->yAlien = top;
        alien->vec->push_back(al);
    }

    top = top - JUMP;

    //row 2
    for (i = 0; i < AMOUNT_ALIEN_ROW; i++) {
        al = (ALIEN*)malloc(sizeof(ALIEN));
        al->live = true;
        al->type = '1';
        al->xAlien = left + i * JUMP;
        al->yAlien = top;
        alien->vec->push_back(al);
    }

    top = top - JUMP;

    //row 3
    for (i = 0; i < AMOUNT_ALIEN_ROW; i++) {
        al = (ALIEN*)malloc(sizeof(ALIEN));
        al->live = true;
        al->type = '2';
        al->xAlien = left + i * JUMP;
        al->yAlien = top;
        alien->vec->push_back(al);
    }

    top = top - JUMP;

    //row 4
    for (i = 0; i < AMOUNT_ALIEN_ROW; i++) {
        al = (ALIEN*)malloc(sizeof(ALIEN));
        al->live = true;
        al->type = '2';
        al->xAlien = left + i * JUMP;
        al->yAlien = top;
        alien->vec->push_back(al);
    }

    top = top - JUMP;

    //row 5
    for (i = 0; i < AMOUNT_ALIEN_ROW; i++) {
        al = (ALIEN*)malloc(sizeof(ALIEN));
        al->live = true;
        al->type = '3';
        al->xAlien = left + i * JUMP;
        al->yAlien = top;
        alien->vec->push_back(al);
    }
}

/*
 * Free memory heap
 */
void destroyAlien()
{

    int i;
    int** shape;
    ALIEN* al;

    //Free all shape stored in memory
    shape = alien->shape1;
    for (i = 0; i < ROW; i++) {
        free(shape[i]);
    }
    free(shape);

    shape = alien->shape2;
    for (i = 0; i < ROW; i++) {
        free(shape[i]);
    }
    free(shape);

    shape = alien->shape3;
    for (i = 0; i < ROW; i++) {
        free(shape[i]);
    }
    free(shape);

    //Free all aliens
    while (!alien->vec->empty()) {
        al = alien->vec[0][0];
        alien->vec->erase(alien->vec->begin());
        free(al);
    }
    delete alien->vec;

    //free struct
    free(alien);
}

int** whatShape(ALIEN* al)
{
    if (al->type == '1')
        return alien->shape1;
    else if (al->type == '2')
        return alien->shape2;
    else
        return alien->shape3;
}

/*
 * Check if aliens win
 */
bool alienVictory()
{

    int i, j, k;
    ALIEN* al;
    int** shape;

    for (i = alien->vec->size() - 1; i >= 0; i--) {
        al = alien->vec[0][i];
        if (al->live == true) {
			if (al->yAlien - 7 / 100.0 + JUMP_Y <= BOTTOM)
				return true;
        }
    }
    return false;
}

/*
 * Verify if the user win
 */
bool userWin()
{
    int i;
    ALIEN* al;

    for (i = 0; i < (int)alien->vec->size(); i++) {
        al = alien->vec[0][i];
        if (al->live == true) {
            return false;
        }
    }
    return true;
}

/*
 * Verify if some alien was killed
 */
bool alienKilled(GLfloat x, GLfloat y)
{
	int i,j,k;
	ALIEN *al;
	int **shape;

	for(i=0; i < (int)alien->vec->size(); i++){
		al = alien->vec[0][i];
		if(al->live == true){
			if (x >= (al->xAlien - 7/100.0 + JUMP_X) && x <= (al->xAlien + JUMP_X) &&
				y >= (al->yAlien - 7/100.0 + JUMP_Y) && y <= (al->yAlien + JUMP_Y)) {
				al->live = false;
				return true;
			}
		}
	}

	return false;
}

/*
 * Give (x,y) indicating the start of alien shoot
 */
void alienShoot()
{

    int r, middle, rTemp;
    int** shape;
    ALIEN* al;

    //initialize random seed
    srand(time(NULL));

    while (true) {
        //Choice one random alien for shoot
        r = rand() % AMOUNT_ALIEN_ROW;

        for (int i = LINES_ALIEN - 1; i >= 0; i--) {

            rTemp = r + (AMOUNT_ALIEN_ROW)*i;

            al = alien->vec[0][rTemp];
            if (al->live == true) {
                shape = whatShape(al);

                middle = COL / 2;
                for (int j = ROW - 1; j >= 0; j--) {
                    if (shape[j][middle]) {
                        createBullet((al->xAlien - j / 100.0) + JUMP_X, (al->yAlien - middle / 100.0) + JUMP_Y, DOWN);
                        return;
                    }
                }
            }
        }
    }
}

extern int GAME_STATE;

/*
 * Move alien in screen
 */
void moveAlien(int value)
{
    int i, j, k;
    ALIEN* al;
    int** shape;

	if (GAME_STATE != GAMESTATE_GAME)
		return;

    //Check where the alien should walk horizontally
    if (LEFT_RIGHT == false) {
        JUMP_X += JUMP / 3.0;
    } else {
        JUMP_X -= JUMP / 3.0;
    }

    //Check if the alien should walk upright
    if ((value % TIME_MOVE_DOWN) == 0) {
        value = 0;
        JUMP_Y -= JUMP / 3.0;
    }

    //Shoot bullet
    if ((value % TIME_SHOOT_ALIEN) == 0) {
        alienShoot();
    }

    //verify if some alien was killed
    //alienKilled();

    for (i = 0; i < (int)alien->vec->size(); i++) {
        al = alien->vec[0][i];
        if (al->live == true) {
            shape = whatShape(al);
            for (j = 0; j < ROW; j++) {
                for (k = 0; k < COL; k++) {
                    if (shape[j][k]) {
                        if (((al->xAlien - k / 100.0) + JUMP_X) > RIGHT) {
                            JUMP_X -= 2 * (JUMP / 3.0);
                            LEFT_RIGHT = true;
                        }
                        if (((al->xAlien - k / 100.0) + JUMP_X) < LEFT) {
                            JUMP_X += 2 * (JUMP / 3.0);
                            LEFT_RIGHT = false;
                        }
                    }
                }
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(TIME_MOVE_ALIEN, moveAlien, value + 1);
}

/*
 * Draw all aliens
 */
void drawAlien()
{

    int i, j, k;
    ALIEN* al;
    int** shape;

    //store matrix
    glPushMatrix();

    glLoadIdentity();

    for (i = 0; i < (int)alien->vec->size(); i++) {
        al = alien->vec[0][i];
        if (al->live == true) {
            shape = whatShape(al);
            for (j = 0; j < ROW; j++) {
                for (k = 0; k < COL; k++) {
                    if (shape[j][k]) {
                        glColor3f(R, G, B);
                        glPointSize(POINT_SIZE);
                        glBegin(GL_POINTS);
                        glVertex2f((al->xAlien - k / 100.0) + JUMP_X, (al->yAlien - j / 100.0) + JUMP_Y);
                        glEnd();
                    }
                }
            }
        }
    }

    glPopMatrix();
}
