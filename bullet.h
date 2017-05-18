#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#include <GL/glut.h>
#include <vector>

#define UP 0
#define DOWN 1

using namespace std;

typedef struct bullet BULLET;

void setBulletInc(GLsizei);
void setWindowDimensions(GLdouble, GLdouble);
void drawBullets();
void createBullet(GLfloat, GLfloat, GLint);
void shotBullet(int);

#endif
