#include "spaceShip.h"
#include "bullet.h"
#include "alien.h"

GLfloat shipX = 0, shipY = 0, cannonPosX, cannonPosY;


/*
Define the initial position parameters of the Spaceship and its cannon
*/
void setInitialSpaceShipPosition(GLfloat x, GLfloat y){
	shipX = x;
	shipY = y;

	cannonPosX = x;
	cannonPosY = -0.75f;
}

/*
Function will read alphanumeric keys of the keyboard
*/
void Keyboard(unsigned char key, int x, int y){
	//Shot missile
	if(key == SPACE){
		createBullet(cannonPosX, cannonPosY, UP);
		glutTimerFunc(10, shotBullet, 1);
	}

	//Leave game
	if(key == ESC)
		destroyAlien();
		exit(0);
}

/*
Function will read special keys (arrow keys), that will move the spaceship
*/
void SpecialKeys(int key, int x, int y){
	if(key == GLUT_KEY_LEFT){
		if(shipX > -0.90)
			shipX -= 0.03;
			cannonPosX = shipX;
	}

	if(key == GLUT_KEY_RIGHT){
		if(shipX < 0.90)
			shipX += 0.03;
			cannonPosX = shipX;
	}

	glutPostRedisplay();
}

/*
Function draw the spaceship of the game
*/
void drawShip(){
	
	//Moves the spaceship to the window bottom
	glTranslatef(0.0f,-0.90f, 0.0f);
	//Update spaceShip position
	glTranslatef(shipX, 0.0f, 0.0f);

	//Left wing
	glColor3f(0.0f, 0.2f, 0.60f);
	glBegin(GL_POLYGON);
		glVertex2f(-0.02f, 0.0f);
		glVertex2f(-0.04f, 0.07f);
		glVertex2f(-0.06f, 0.0f);
		glVertex2f(-0.04f, -0.07f);
	glEnd();

	//Right wing
	glBegin(GL_POLYGON);
		glVertex2f(0.02f, 0.0f);
		glVertex2f(0.04f, 0.07f);
		glVertex2f(0.06f, 0.0f);
		glVertex2f(0.04f, -0.07f);
	glEnd();

	//Base
	glColor3f(0.81f,0.80f,0.82f);
	glBegin(GL_POLYGON);
		glVertex2f(0.0f, 0.14f);
		glVertex2f(0.03f, 0.0f);
		glVertex2f(0.0f, -0.05f);
		glVertex2f(-0.03f, 0.0f);
	glEnd();

	//Window
	glTranslatef(0.0f,0.04f, 0.0f);
	glColor3f(0.0f, 0.66f, 0.80f);
	glBegin(GL_POLYGON);
		glVertex2f(0.01f, 0.015f);
		glVertex2f(0.01f, -0.015f);
		glVertex2f(-0.01f, -0.015f);
		glVertex2f(-0.01f, 0.015f);
	glEnd();
}
