#pragma once

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <cstdio>

#define GAMESTATE_GAME 0
#define GAMESTATE_WON 1
#define GAMESTATE_LOST 2

using namespace std;

void drawLives();
void playerWasHit();

void drawLostScreen();
void drawWonScreen();

void startVerifiers(int);

void initGame();
