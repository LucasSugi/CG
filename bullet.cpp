/*
 *  	Bullets - Controls the bullets moves
*/

#include "bullet.h"
#include <stdio.h>

struct bullet {
    GLfloat xPos;
    GLfloat yPos;
    GLint direction;
    bool visible;
};

/**	Bullets	   */
vector<BULLET> bullet;
GLfloat inc;
GLdouble top, bottom;

/**	Sets the bullet increment	*/
void setBulletInc(GLsizei height)
{
    inc = (GLfloat)2 / height;
}

/**	Sets window dimensions	*/
void setWindowDimensions(GLdouble WTop, GLdouble WBottom)
{
    top = WTop;
    bottom = WBottom;
}

/** 	Draws the bullets on the screen		*/
void drawBullets()
{

    if (!bullet.empty()) {
        for (vector<BULLET>::iterator it = bullet.begin(); it != bullet.end(); it++) {
            if (it->visible) {
                glColor3f(1.0f, 0.0f, 0.0f);
                glPointSize(5.0);
                glBegin(GL_POINTS);
                glVertex2f(it->xPos, it->yPos);
                glEnd();
            }
        }
    }
}

/** 	Creates a new bullet and inserts in the bullets vector	 */
void createBullet(GLfloat x, GLfloat y, GLint direction)
{

    BULLET b;

    b.xPos = x;
    b.yPos = y;
    b.direction = direction;
    b.visible = true;

    bullet.push_back(b);
}

/**	Bullets Timer function	*/
void shotBullet(int value)
{

    GLfloat v = inc * value;

    // Moves the bullets
    if (!bullet.empty()) {
        for (vector<BULLET>::iterator it = bullet.begin(); it != bullet.end(); it++) {
            if (it->direction == DOWN) {
                it->yPos -= v;
                if (it->yPos <= bottom) {
                    it->visible = false;
                }
            } else if (it->direction == UP) {
                it->yPos += v;
                if (it->yPos >= top) {
                    it->visible = false;
                }
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(10 * bullet.size(), shotBullet, value);
}
