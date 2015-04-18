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
#include "Beizer.h"


enum MenuType{
	MENU_ADD_BEIZER,
	MENU_REMOVE_BEIZER
};

enum SelectType{
	SELECT_BEIZER,
	SELECT_HANDLE
};

// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;
bool clickedDown = false;
int activeHandle = -1;
int activeBeizer = -1;
vector<Beizer> gBeizers;
SelectType G_SELECT_TYPE = SELECT_HANDLE;
double clickedAtX = -1;
double clickedAtY = -1;

// 
// Functions that draw basic primitives
//

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

void DrawSelectType(){
	double x = .2;
	double y = screen_y / 100 - .3;
	if (G_SELECT_TYPE == SELECT_BEIZER){
		DrawText(x, y, "Selecting whole curve");
	}
	if (G_SELECT_TYPE == SELECT_HANDLE){
		DrawText(x, y, "Selecting control points");
	}
	DrawText(x, y - .2, "Press \"s\" to switch");
}
//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < gBeizers.size(); i++){
		gBeizers[i].DrawControlPoints();
		gBeizers[i].DrawCurve();
	}
	DrawSelectType();
	glutSwapBuffers();
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c) 
	{
		case 27: // escape character means to quit the program
			exit(0);
			break;
		case 's':
			if (G_SELECT_TYPE == SELECT_BEIZER){
				G_SELECT_TYPE = SELECT_HANDLE;
				if (activeBeizer != -1){
					gBeizers[activeBeizer].DeactivateBeizer();
				}
				activeBeizer = -1;
			}
			else {
				G_SELECT_TYPE = SELECT_BEIZER;
				clickedDown = false;
				if (activeBeizer != -1){
					gBeizers[activeBeizer].DeactivateHandle();
				}
				activeBeizer = activeHandle = -1;
			}
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
	gluOrtho2D(0, screen_x/100, 0, screen_y/100);
	glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	//switch to bottom left
	y = screen_y - y;
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		for (int i = 0; i < gBeizers.size(); i++){
			bool wasActive = false;
			if (gBeizers[i].IsActive()){
				gBeizers[i].DeactivateBeizer();
				wasActive = true;
			}
			int handle = gBeizers[i].MouseHitHandle(x, y);
			if (handle != -1){
				activeBeizer = i;
				activeHandle = handle;
				if (G_SELECT_TYPE == SELECT_HANDLE){
					gBeizers[activeBeizer].ActivateHandle(handle);
					clickedDown = true;
					break;
				}
				if (G_SELECT_TYPE == SELECT_BEIZER && !wasActive){
					gBeizers[activeBeizer].ActivateBeizer();
					clickedAtX = x;
					clickedAtY = y;
					clickedDown = true;
					break;
				}
			}
		}
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		if (activeBeizer != -1){
			if (G_SELECT_TYPE == SELECT_HANDLE){
				gBeizers[activeBeizer].DeactivateHandle();
				clickedDown = false;
				activeBeizer = activeHandle = -1;
			}
			if (G_SELECT_TYPE == SELECT_BEIZER){
				clickedDown = false;
				clickedAtX = clickedAtY = -1;
			}
		}
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	glutPostRedisplay();
}
void movement(int x, int y){
	y = screen_y - y;
	if (activeBeizer != -1){
		if (clickedDown && G_SELECT_TYPE == SELECT_HANDLE){
			gBeizers[activeBeizer].SetHandlePoint(activeHandle, x, y);
		}
		if (clickedDown && G_SELECT_TYPE == SELECT_BEIZER){
			double differenceX = x - clickedAtX;
			double differenceY = y - clickedAtY;
			clickedAtX = x;
			clickedAtY = y;
			gBeizers[activeBeizer].Move(differenceX, differenceY);
		}
	}
}
// Your initialization code goes here.
void InitializeMyStuff()
{
	gBeizers.push_back(Beizer());
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
	glutMotionFunc(movement);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
