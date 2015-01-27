// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#include <cmath>
#include <cstring>
#include "Globals.h"
#include "Circle.h"
#include <vector>
#include <cstdlib>
#include <time.h>
#include "glut.h"
using namespace std;


// Global Variables (Only what you need!)
const int GLOBAL_CIRCLES = 4;
const double RANDOM_VELOCITY_MAX = 10000;
const int MAX_FRAME_RATE = 120;
int strobe = 0;



// 
// Functions that draw basic primitives
//
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
}
double random(int end){
	return (rand() % end) * 1.0;
}
double random(int start, int end){
	return (rand() % end + start) * 1.0;
}
double random(int start, int end, bool percentage){
	return ((rand() % end + start) * 1.0) / end;
}
//Gets a number between 0-1 and offsets it if desired, set scaleDown to 1 if you don't want scaling
double random(){
	//get a number between 0 and end (10,000 in this case)
	double random = double(rand() % int(RANDOM_VELOCITY_MAX));
	//convert the number from 0-10,000, to 0-1.
	//larger num for accuracy adds more accuracy, duh.
	random /= double(RANDOM_VELOCITY_MAX);
	//now we divide by a scale down factor if smaller numbers are needed
	random /= 5;
	random -= 0.25;
	return random;
}

//
// GLUT callback functions
//

void swapBG(){
	return;
}
// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	physics->HandleCollisions();
	physics->ApplyGravity();
	physics->ApplyAirFriction();
	physics->UpdateObjects();

	glColor3d(0,0,0);

	glutSwapBuffers();
	if (strobe % 60 == 0){
		swapBG();
		strobe = 0;
	}
	/*
	TODO: Limit fps. write a timer function
	then put glutPostRedisplay inside of it.
	*/
	strobe += 1;
	glutPostRedisplay();
}

// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	double startingX = random(screen_x);
	double startingY = screen_y + 100;
	Point startingPoint = Point();
	startingPoint.setPoint(startingX, startingY);
	double v = random(0, 1000, true);
	startingPoint.setVelocity(random(), -0.9);
	/*
	TODO: Ask Bart why it will not display colors
	*/
	double red = random(0, 1000, true);
	double green = random(0, 1000, true);
	double blue = random(0, 1000, true);
	if (red >= 0.9){
		red -= 0.9;
	}
	if (green >= 0.9){
		green -= 0.9;
	}
	if (blue >= 0.9){
		blue -= 0.9;
	}
	Color color = Color(red, green, blue);
	/*
	TODO: Ask Bart why my inheritence is all weird.
	Place a break point at shapes.push_back in order to see it in the
	autos variable list
	*/
	Circle *circleToMake = new Circle(startingPoint, random(10, 50), color);
	switch (c) 
	{
		case 27: // escape character means to quit the program
			exit(0);
			break;
		case 'b':
			physics->Collidables.push_back(circleToMake);
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		physics->FindMouseCollisions(x, y, screen_x, screen_y);
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		for each(Shape * shape in physics->Collidables){
			shape->shapePoint.setVelocityX(random());
			shape->shapePoint.setVelocityY(0.7);
		}
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	srand(time(NULL));
	double startingX = random(screen_x);
	double startingY = random(screen_y);
	Point startingPoint = Point(startingX, startingY);
	for (int i = 0; i < GLOBAL_CIRCLES; i++){
		startingX = random(screen_x);
		startingY = random(screen_y);
		startingPoint.setPoint(startingX, startingY);
		double v = random(0, 1000, true);
		startingPoint.setVelocity(random(), random());
		/*
		TODO: Ask Bart why it will not display colors
		*/
		Color color = Color(random(0, 1000, true), random(0, 1000, true), random(0, 1000, true));
		/*
		TODO: Ask Bart why my inheritence is all weird.
		Place a break point at shapes.push_back in order to see it in the 
		autos variable list
		*/
		Circle *circleToMake = new Circle(startingPoint, random(10, 50), color);
		physics->Collidables.push_back(circleToMake);

		if (startingX == 0){
			startingX += 1;
		}
		if (startingY == 0){
			startingY += 1;
		}
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("This appears in the title bar");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
