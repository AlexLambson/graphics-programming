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
#include "Camera.h"
#include "Terrain.h"
#include "Helpers.h"
#include "glut.h"


// Global Variables (Only what you need!)
double screen_x = 1280;
double screen_y = 720;
//will be used to create n+1 points
int sizeX = 200;
int sizeY = 200;
Camera gCamera = Camera(25, 25, 12.0); 
Terrain gTerrain = Terrain(sizeX, sizeY, true);
double waterHeight = 4;


void SetTopView(int w, int h)
{
	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0;
	double world_margin_y = 0;
	gluOrtho2D(-world_margin_x, sizeX + world_margin_x, -world_margin_y, sizeY + world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}
void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble)w / (GLdouble)h;
	gluPerspective(
		/* field of view in degree */ 90.0,
		/* aspect ratio */ aspectRatio,
		/* Z near */ .1, /* Z far */ 200);
	glMatrixMode(GL_MODELVIEW);
}
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

void DrawFilter()
{
	// go into 2D mode
	SetTopView(sizeX, sizeY);
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	glColor4d(0, 0, 0.7, 0.6);
	glBegin(GL_QUADS);
		glVertex2d(0, 0);
		glVertex2d(sizeX, 0);
		glVertex2d(sizeX, sizeY);
		glVertex2d(0, sizeY);
	glEnd();
	SetPerspectiveView(sizeX, sizeY);
}

//
// GLUT callback functions
//
void drawCamera(){
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	float zLevel = 1;
	float x = gCamera.GetPosition().x;
	float y = gCamera.GetPosition().y;
	float z = gCamera.GetPosition().z;
	double dx = gCamera.GetDX();
	double dy = gCamera.GetDY();
	double dz = 0;
	float at_x = gCamera.GetLookAt().x;
	float at_y = gCamera.GetLookAt().y;
	float at_z = gCamera.GetLookAt().z;
	gluLookAt(x, y, z, at_x, at_y, at_z, 0, 0, 1);
	/*
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	gluLookAt(-3, -3, 7, 3, 3, 0, 0, 0, 1);
	*/
}
// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Test lines that draw all three shapes and some text.
	// Delete these when you get your code working.
	drawCamera();
	gTerrain.Draw(GROUND);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (gCamera.GetPosition().z < gTerrain.WaterPoints[gCamera.GetPosition().x][gCamera.GetPosition().y].z){
		DrawFilter();
	}
	else {
		gTerrain.Draw(WATER);
	}
	glDisable(GL_BLEND);
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
		case 'w':
			gCamera.HandleKey(Key::UP);
			break;
		case 'a':
			// do something when 'b' character is hit.
			gCamera.HandleKey(Key::LEFT);
			break;
		case 's':
			gCamera.HandleKey(Key::DOWN);
			break;
		case 'd':
			gCamera.HandleKey(Key::RIGHT);
			break;
		case '=':
			gCamera.ChangeSpeed(0.5);
			break;
		case '-':
			gCamera.ChangeSpeed(-0.5);
			break;
		case 'x':
			waterHeight -= 0.1;
			gTerrain.GenerateTerrain(WATER);
			break;
		case 'c':
			waterHeight += 0.1;
			gTerrain.GenerateTerrain(WATER);
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
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);
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
	glEnable(GL_CULL_FACE);
	SetPerspectiveView(sizeX, sizeY);
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
