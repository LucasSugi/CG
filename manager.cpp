#include "manager.h"

int playerLives = 3;

void drawLives()
{
    char str[50];

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(255, 255, 255);
    glRasterPos2f(-0.95, 0.9);

    sprintf(str, "Lives: %d", playerLives);

    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)str);
}

void drawLostScreen()
{
}

void drawWinScreen()
{
}

void playerWasHit()
{
    playerLives--;

    if (playerLives <= 0) {
        printf("PLAYER LOST!!!!\n");
    }
}
