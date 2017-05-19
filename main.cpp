#include "bullet.h"
#include "alien.h"
#include "spaceShip.h"


// Controls the window size
GLsizei windowWidth = 700, windowHeight = 500;

// Assigns the Clipping Window
GLdouble windowLeft = -1.0f, windowRight = 1.0f, windowBottom = -1.0f, windowTop = 1.0f;

// Initial position of the spaceShip
GLfloat shipPosX = 0.0f, shipPosY = 0.0f;

/**	Rendering Funcion	*/
void draw(){
	
	//Changes to the 
	glMatrixMode(GL_MODELVIEW);
	//Initialize the transformations matrix
	glLoadIdentity();
	
	// Cleans the screen
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Draw the bullets on the screen
	drawBullets();
	drawShip();
	drawAlien();
	
	// Update the screen
	glutSwapBuffers();
	glFlush();	
}

/**	Resizing Funcion	*/
void reshapeWindow(int width, int height){
	if (height == 0) height = 1;

	windowWidth = width;
	windowHeight = height;

	glViewport(0, 0, windowWidth, windowHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(width <= height)
		gluOrtho2D(windowLeft, windowRight, windowBottom*height/width, windowTop*height/width);
	else
		gluOrtho2D(windowLeft*width/height, windowRight*width/height, windowBottom, windowTop);
}

/**	Boot Funcion	*/
void initializeParameters(){
	
	// Sets the Clear Color to black
	glClearColor(0.0f, 0.16f, 0.16f, 0.0f);
	
	// Initializes the matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Initializes the clipping window and viewport
	gluOrtho2D(windowLeft, windowRight, windowBottom, windowTop);
	glViewport(0, 0, windowWidth, windowHeight);
	
	setBulletInc(windowHeight);
	setInitialSpaceShipPosition(shipPosX, shipPosY);
	setWindowDimensions(windowTop, windowBottom);
	
	//Create alien
	createAlien(windowLeft,windowRight,windowBottom,windowTop,0,0,windowWidth,windowHeight,18);
}


/**	Main Function	*/
int main(int argc, char *argv[]){
	
	// Initialize 
	glutInit(&argc, argv);	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	
	// Assigns the window initial position and size
	glutInitWindowSize(windowWidth, windowHeight);
	
	// Creates the window
	glutCreateWindow("S P A C E -- I N V A D E R S");

	// Defines the rendering function
	glutDisplayFunc(draw);

	// Defines the resizing function
	glutReshapeFunc(reshapeWindow);
	
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(Keyboard);

	glutTimerFunc(10, moveAlien, 0);
	initializeParameters();

	// Starts the processing and wait user interactions
	glutMainLoop();

	// End
	return 0;
}
