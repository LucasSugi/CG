#include "manager.h"

int playerLives = 3;
int GAME_STATE = GAMESTATE_GAME;

extern bool alienVictory();
extern bool userWin();

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
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glColor3ub(255, 255, 255);
	glRasterPos2f(-0.4f, 0.0f);

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"You Lost! (SPACE to play again)");
}

void drawWonScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glColor3ub(255, 255, 255);
	glRasterPos2f(-0.4f, 0.0f);

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"You Won! (SPACE to play again)");
}


void playerWasHit()
{
    playerLives--;

    if (playerLives <= 0) {
		GAME_STATE = GAMESTATE_LOST;
    }
}

void startVerifiers(int value)
{
	if (GAME_STATE != GAMESTATE_GAME)
		return;

	if (alienVictory()) {
		GAME_STATE = GAMESTATE_LOST;
		glutPostRedisplay();
	}

	if (userWin()) {
		GAME_STATE = GAMESTATE_WON;
		glutPostRedisplay();
	}

	glutTimerFunc(250, startVerifiers, 1);
}

extern void moveAlien(int);
extern void shotBullet(int);
extern void initializeParameters(void);

void initGame()
{
	playerLives = 3;
    glutTimerFunc(10, moveAlien, 0);
    glutTimerFunc(16, shotBullet, 1);
    initializeParameters();
	startVerifiers(1);
}
