#ifndef _SPACESHIP_HPP_
#define _SPACESHIP_HPP_

#include <GL/glut.h>
#include <stdio.h>

#define ESC 27
#define SPACE 32

void Keyboard(unsigned char, int, int);
void SpecialKeys(int, int, int);
void setInitialSpaceShipPosition(GLfloat, GLfloat);
void drawShip();

#endif
