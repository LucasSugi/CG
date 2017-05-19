#ifndef _ALIEN_H_
#define _ALIEN_H_

typedef struct control_alien CONTROL_ALIEN;

/*
 * Create aliens
 * left,right,bottom and top MUST BE the same values of gluOrtho2D
 * nAlien is the amount of alien per LINE
 */
void createAlien(float left, float right, float bottom, float top, float xVmin, float xVmax, float yVmin, float yVmax, int nAlien);

/*
 * Change the dificulty of game
 */
void changeDificulty(int time_move_alien, int time_shoot_alien);

/*
 * Verify if user win
 */
bool userWin();

/*
 * Free memory heap
 */
void destroyAlien();

/*
 * Check if aliens win
 */
bool alienVictory();

/*
 * Move alien in screen
 * This function should be used in glutTimeFunc
 * Should be passed ZERO for this function 
 */
void moveAlien(int);

/*
 * Draw all aliens
 */
void drawAlien();

#endif
