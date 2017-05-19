#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <GL/glut.h>
#include "alien.h"

using namespace std;

//Define the size of alien's file
#define ROW 8
#define COL 8

//This two variable is used to set the initial position of first alien
//The variable cause one displacement in LEFT and TOP coordinates
int INC_X  = 10;
int INC_Y  = 10;

//This variable defines how many aliens have per line
int AMOUNT_ALIEN_ROW;

//This defines how lines of aliens have space invaders
int LINES_ALIEN = 5;

//This variable define how long is the movement of one alien in horizontal
int TIME_MOVE_DOWN = 50;

//This variable defines the amount of jump in horizontal and vertical
int JUMP = 4;

//This variable MUST BE the same values of parameters in gluOrtho2D
int LEFT, RIGHT, BOTTOM, TOP;

//This variable defines the accumulated amount of jump in horizontal and vertical
int JUMP_X,JUMP_Y = 0;

//This variable will be used for check where the alien need to move
bool LEFT_RIGHT;
bool BOTTOM_TOP;

//RGB color for alien
float R = 0.0f, G = 1.0f, B = 0.0f;

//This variable resize all aliens
double SCALE_FACTOR = 0.5f;

//This variable define size of point that will be used for draw one alien
float POINT_SIZE = 2.0f;

typedef struct alien{
	int xAlien,yAlien;
	bool live;
	char type;
} ALIEN;

typedef struct control_alien{
	int **shape1;
	int **shape2;
	int **shape3;
	vector<ALIEN*> *vec;
} CONTROL_ALIEN;

CONTROL_ALIEN *alien;

/*
 * Read content of alien's file
 */
int **readFile(const char *filename){
	
	int c;	
	FILE *fp;
	int **shape;
	
	//read the shape of alien1	
	fp = fopen(filename,"r");

	if(fp == NULL) return NULL;

	//create matrix
	shape = (int**) malloc(sizeof(int*) * ROW);

	//It's necessary that file have 8 rows and cols 
	for(int i=0;i<ROW;i++){
		shape[i] = (int*) malloc(sizeof(int) * COL);
		for(int j=0;j<COL;j++){
			c = fgetc(fp);
			shape[i][j] = c-48;	
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
void createAlien(float left,float right,float bottom,float top,int nAlien){
	
	int i;
	ALIEN *al;
	
	//Create struct
	alien = (CONTROL_ALIEN*) malloc(sizeof(CONTROL_ALIEN));
	
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
	top = (top / SCALE_FACTOR) - INC_Y;
	left = (left / SCALE_FACTOR) + INC_X;
		
	//row 1
	for(i=0;i<AMOUNT_ALIEN_ROW;i++){
		al = (ALIEN*) malloc(sizeof(ALIEN));	
		al->live = true;
		al->type = '1';
		al->xAlien = left + i*(COL+JUMP);
		al->yAlien = top;
		alien->vec->push_back(al);
	}
	
	top = top - (ROW + JUMP);

	//row 2
	for(i=0;i<AMOUNT_ALIEN_ROW;i++){
		al = (ALIEN*) malloc(sizeof(ALIEN));	
		al->live = true;
		al->type = '1';
		al->xAlien = left + i*(COL+JUMP);
		al->yAlien = top;
		alien->vec->push_back(al);
	}

	top = top - (ROW + JUMP);

	//row 3
	for(i=0;i<AMOUNT_ALIEN_ROW;i++){
		al = (ALIEN*) malloc(sizeof(ALIEN));	
		al->live = true;
		al->type = '2';
		al->xAlien = left + i*(COL+JUMP);
		al->yAlien = top;
		alien->vec->push_back(al);
	}
	
	top = top - (ROW + JUMP);

	//row 4
	for(i=0;i<AMOUNT_ALIEN_ROW;i++){
		al = (ALIEN*) malloc(sizeof(ALIEN));	
		al->live = true;
		al->type = '2';
		al->xAlien = left + i*(COL+JUMP);
		al->yAlien = top;
		alien->vec->push_back(al);
	}
	
	top = top - (ROW + JUMP);

	//row 5
	for(i=0;i<AMOUNT_ALIEN_ROW;i++){
		al = (ALIEN*) malloc(sizeof(ALIEN));	
		al->live = true;
		al->type = '3';
		al->xAlien = left + i*(COL+JUMP);
		al->yAlien = top;
		alien->vec->push_back(al);
	}
}

/*
 * Free memory heap
 */
void destroyAlien(){
	
	int i;
	int **shape;
	ALIEN *al;
	
	//Free all shape stored in memory
	shape = alien->shape1;
	for(i=0;i<ROW;i++){
		free(shape[i]);
	}
	free(shape);

	shape = alien->shape2;
	for(i=0;i<ROW;i++){
		free(shape[i]);
	}
	free(shape);

	shape = alien->shape3;
	for(i=0;i<ROW;i++){
		free(shape[i]);
	}
	free(shape);
		
	//Free all aliens
	while( !alien->vec->empty() ){
		al = alien->vec[0][0];	
		alien->vec->erase(alien->vec->begin());
		free(al);
	}
	delete alien->vec;
	
	//free struct
	free(alien);
}

int **whatShape(ALIEN *al){
	if(al->type == '1') return alien->shape1;
	else if(al->type == '2') return alien->shape2;
	else return alien->shape3;
}

/*
 * Check if aliens win
 */
bool alienVictory(){	
	
	int i,j,k;
	ALIEN *al;
	int **shape;

	for(i=0;i<(int)alien->vec->size();i++){
		al = alien->vec[0][i];
		if(al->live == true){
			shape = whatShape(al);
			for(j=0;j<ROW;j++){
				for(k=0;k<COL;k++){
					if(shape[j][k]){
						if( (al->yAlien-j+JUMP_Y)*SCALE_FACTOR < BOTTOM){
							JUMP = 0;
							return true;
						}
					}	
				}
			}
		}
	}
	return false;	
}

/*
 * Verify if some alien was killed
 */
bool alienKilled(int x, int y){

	int i,j,k;
	ALIEN *al;
	int **shape;

	for(i=0;i<(int)alien->vec->size();i++){
		al = alien->vec[0][i];
		if(al->live == true){
			shape = whatShape(al);
			for(j=0;j<ROW;j++){
				for(k=0;k<COL;k++){
					if(shape[j][k]){
						if( (al->yAlien-j+JUMP_Y)*SCALE_FACTOR == y && (al->xAlien-k+JUMP_X)*SCALE_FACTOR == x){
							al->live = false;
							return true;
						}
					}	
				}
			}
		}
	}
	return false;
}

/*
 * Give (x,y) indicating the start of alien shoot
 */
void alienShoot(int *x, int *y){

	int r,middle,rTemp;
	int **shape;	
	ALIEN *al;

	//initialize random seed
	srand( time(NULL) );

	//Choice one random alien for shoot
	r = rand() % AMOUNT_ALIEN_ROW;
		
	for(int i=LINES_ALIEN-1;i>=0;i--){	
	
		rTemp = r + (AMOUNT_ALIEN_ROW)*i;

		al = alien->vec[0][rTemp];
		if(al->live == true){
			shape = whatShape(al);
	
			middle = COL/2;	
			for(int j=ROW-1;j>=0;j--){
				if(shape[j][middle]){
					*x = j;
					*y = middle;
					break;
				}	
			}
			return;
		}
	}
}

/*
 * Move alien in screen
 */
void moveAlien(int value){
	
	int i,j,k;
	ALIEN *al;
	int **shape;
	
	//Check where the alien should walk horizontally	
	if(LEFT_RIGHT == false){
		JUMP_X += JUMP; 
	}
	else{
		JUMP_X -= JUMP;	
	}
	
	//Check if the alien should walk upright
	if( (value % TIME_MOVE_DOWN) == 0){
		value = 0;
		JUMP_Y -= JUMP;	
	}

	for(i=0;i<(int)alien->vec->size();i++){
		al = alien->vec[0][i];
		if(al->live == true){
			shape = whatShape(al);
			for(j=0;j<ROW;j++){
				for(k=0;k<COL;k++){
					if(shape[j][k]){
						if( (al->xAlien-k+JUMP_X)*SCALE_FACTOR > RIGHT){
							JUMP_X -= 2*JUMP;
							LEFT_RIGHT = true;
						}
						if( (al->xAlien-k+JUMP_X)*SCALE_FACTOR < LEFT){
							JUMP_X += 2*JUMP;
							LEFT_RIGHT = false;
						}
					}	
				}
			}
		}
	}
	
	glutPostRedisplay();
	glutTimerFunc(1000,moveAlien,value+1);
}

/*
 * Draw all aliens
 */
void drawAlien(){

	int i,j,k;
	ALIEN *al;
	int **shape;
	
	//store matrix	
	glPushMatrix();

	//resizing alien	
	glScalef(SCALE_FACTOR,SCALE_FACTOR,1.0f);

	for(i=0;i<(int)alien->vec->size();i++){	
		al = alien->vec[0][i];
		if(al->live == true){
			shape = whatShape(al);
			for(j=0;j<ROW;j++){
				for(k=0;k<COL;k++){
					if(shape[j][k]){
						glColor3f(R,G,B);
						glPointSize(POINT_SIZE);
						glBegin(GL_POINTS);
							glVertex2f(al->xAlien-k+JUMP_X,al->yAlien-j+JUMP_Y);
						glEnd();
					}
				}
			}
		}
	}

	glPopMatrix();
}
