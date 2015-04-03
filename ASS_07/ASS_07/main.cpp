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
#include <iostream>
#include <random>
#include <time.h>
#include "Structs.h"
#include "Maze.h"
#include "glut.h"


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;
Maze gMaze;
int mazeX = 5;
int mazeY = 4;

void SetTopView(int w, int h)
{
	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0.5;
	double world_margin_y = 0.5;
	gluOrtho2D(-world_margin_x, mazeX + world_margin_x, -world_margin_y, mazeY + world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}

void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		/* field of view in degree */ 70.0,
		/* aspect ratio */ aspectRatio,
		/* Z near */ .1, /* Z far */ 30.0);
	glMatrixMode(GL_MODELVIEW);
}
//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{	
	/*double fps = GetFramesPerSecond();
	double DT = 1.0 / fps;*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (Globals::current_view == perspective_view) {
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		gluLookAt(-3, -3, 7, 3, 3, 0, 0, 0, 1); //perspective of camera (standing off, center point, updirection/rotation)
	}
	else if (Globals::current_view == top_view) {
		glDisable(GL_DEPTH_TEST);
		glLoadIdentity();
	}
	else { //current_view == rat_view
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		float zLevel = gMaze.rat.GetZ() + 0.2;
		float x = gMaze.rat.GetX();
		float y = gMaze.rat.GetY();
		float z = gMaze.rat.GetZ();
		double dx = gMaze.rat.GetDX();
		double dy = gMaze.rat.GetDY();
		double dz = 0;
		float at_x = x + dx;
		float at_y = y + dy;
		float at_z = zLevel;
		gluLookAt(x, y, zLevel, at_x, at_y, at_z, 0, 0, 1);
	}
	gMaze.Draw();
	glutSwapBuffers();
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	CellWalls walls = gMaze.GetCellWalls(gMaze.rat.GetIndex());
	switch (c) 
	{
		case 27: // escape character means to quit the program
			exit(0);
			break;
		case 'w':
			gMaze.rat.HandleKey(Key::UP, walls);
			break;
		case 's':
			gMaze.rat.HandleKey(Key::DOWN, walls);
			break;
		case 'a':
			gMaze.rat.HandleKey(Key::LEFT, walls);
			break;
		case 'd':
			gMaze.rat.HandleKey(Key::RIGHT, walls);
			break;
		case 't':
			Globals::current_view = top_view;
			SetTopView(screen_x, screen_y);
			break;
		case 'p':
			Globals::current_view = perspective_view;
			SetPerspectiveView(screen_x, screen_y);
			break;
		case 'r':
			Globals::current_view = rat_view;
			SetPerspectiveView(screen_x, screen_y);
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);

	if (Globals::current_view == top_view)
	{
		SetTopView(w, h);
	}
	else if (Globals::current_view == perspective_view)
	{
		SetPerspectiveView(w, h);
	}
	else // current_view == rat_view
	{
		SetPerspectiveView(w, h);
	}
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
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	gMaze = Maze(mazeX, mazeY);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	srand(time(NULL));
	std::cout << "Enter maze size as 'x y':     ";
	std::cin >> mazeX >> mazeY;
	screen_x = 200 * mazeX;
	screen_y = 200 * mazeY;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
