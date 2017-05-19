#ifndef _ALIEN_H_
#define _ALIEN_H_

typedef struct control_alien CONTROL_ALIEN;

/*
 * Create aliens
 * left,right,bottom and top MUST BE the same values of gluOrtho2D
 * nAlien is the amount of alien per LINE
 */
CONTROL_ALIEN *createAlien(float left,float right,float bottom,float top,int nAlien);	

/*
 * Free memory heap
 */
void destroyAlien();

/*
 * Check if aliens win
 */
bool alienVictory();

/*
 * Verify if some alien was killed
 * (x,y) is the bullet's coordinates
 */
bool alienKilled(int , int );

/*
 * Give (x,y) indicating the start of alien shoot
 */
void alienShoot(int *, int *);

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
