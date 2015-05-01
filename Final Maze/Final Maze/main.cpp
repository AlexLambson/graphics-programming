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
#include <conio.h>
#include <ctype.h>
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
const int num_textures = 2;
static GLuint texName[num_textures];
clock_t startTime = clock();

gliGenericImage *readTgaImage(char *filename)
{
	FILE *file;
	gliGenericImage *image;

	file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Error: could not open \"%s\"\n", filename);
		return NULL;
	}
	image = gliReadTGA(file, filename);
	fclose(file);
	if (image == NULL) {
		printf("Error: could not decode file format of \"%s\"\n", filename);
		return NULL;
	}
	return image;
}


// Generic image loader code.
gliGenericImage *readImage(char *filename)
{
	size_t size = strlen(filename);
	if (toupper(filename[size - 3]) == 'T' && toupper(filename[size - 2]) == 'G' && toupper(filename[size - 1]) == 'A')
	{
		gliGenericImage * result = readTgaImage(filename);
		if (!result)
		{
			cerr << "Error opening " << filename << endl;
			_getch();
			exit(1);
		}
		return result;
	}
	else
	{
		cerr << "Unknown Filetype!\n";
		_getch();
		exit(1);
	}
}

// This resets the edges of the texture image to a given "border color".
// You must call this for clamped images that do not take up the whole polygon.
// Otherwise, the texture edges will smear outward across the rest
// of the polygon.
void SetBorder(gliGenericImage * image)
{
	// set a border color.
	unsigned int border_r = 50;
	unsigned int border_g = 50;
	unsigned int border_b = 255;
	int x, y;
	y = 0;
	for (x = 0; x<image->width; x++)
	{
		image->pixels[3 * (y*image->width + x) + 0] = border_r;
		image->pixels[3 * (y*image->width + x) + 1] = border_g;
		image->pixels[3 * (y*image->width + x) + 2] = border_b;
	}
	y = 1;
	for (x = 0; x<image->width; x++)
	{
		image->pixels[3 * (y*image->width + x) + 0] = border_r;
		image->pixels[3 * (y*image->width + x) + 1] = border_g;
		image->pixels[3 * (y*image->width + x) + 2] = border_b;
	}
	y = image->height - 1;
	for (x = 0; x<image->width; x++)
	{
		image->pixels[3 * (y*image->width + x) + 0] = border_r;
		image->pixels[3 * (y*image->width + x) + 1] = border_g;
		image->pixels[3 * (y*image->width + x) + 2] = border_b;
	}
	y = image->height - 2;
	for (x = 0; x<image->width; x++)
	{
		image->pixels[3 * (y*image->width + x) + 0] = border_r;
		image->pixels[3 * (y*image->width + x) + 1] = border_g;
		image->pixels[3 * (y*image->width + x) + 2] = border_b;
	}

	x = 0;
	for (y = 0; y<image->height; y++)
	{
		image->pixels[3 * (y*image->width + x) + 0] = border_r;
		image->pixels[3 * (y*image->width + x) + 1] = border_g;
		image->pixels[3 * (y*image->width + x) + 2] = border_b;
	}
	x = 1;
	for (y = 0; y<image->height; y++)
	{
		image->pixels[3 * (y*image->width + x) + 0] = border_r;
		image->pixels[3 * (y*image->width + x) + 1] = border_g;
		image->pixels[3 * (y*image->width + x) + 2] = border_b;
	}
	x = image->width - 1;
	for (y = 0; y<image->height; y++)
	{
		int index = 3 * (y*image->width + x);
		image->pixels[index + 0] = border_r;
		image->pixels[index + 1] = border_g;
		image->pixels[index + 2] = border_b;
	}
	x = image->width - 2;
	for (y = 0; y<image->height; y++)
	{
		int index = 3 * (y*image->width + x);
		image->pixels[index + 0] = border_r;
		image->pixels[index + 1] = border_g;
		image->pixels[index + 2] = border_b;
	}
}
// Return true if h is a perfect power of 2 (up to 4096)
bool PowerOf2(int h)
{
	if (h != 2 && h != 4 && h != 8 && h != 16 && h != 32 && h != 64 && h != 128 &&
		h != 256 && h != 512 && h != 1024 && h != 2048 && h != 4096)
		return false;
	else
		return true;
}
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
		float zLevel = gMaze.rat.GetZ() + 0.28;
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
	gMaze.Draw(texName);
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
		case 'q':
			gMaze.rat.HandleKey(Key::Q, walls);
			break;
		case 'e':
			gMaze.rat.HandleKey(Key::E, walls);
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
	gliGenericImage *image[num_textures];
	int n = 0;
	image[n++] = readImage("grass.tga");
	image[n++] = readImage("brick.tga");
	glGenTextures(num_textures, texName);

	for (int i = 0; i<num_textures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		int repeats = false;
		int needs_border = false; // Needed if clamping and not filling the whole polygon.
		if (repeats)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		}
		if (needs_border)
		{
			// set a border.
			SetBorder(image[i]);
		}

		bool mipmaps = false;
		if (!PowerOf2(image[i]->height) || !PowerOf2(image[i]->width))
		{
			// WARNING: Images that do not have width and height as 
			// powers of 2 MUST use mipmaps.
			mipmaps = true;
		}

		if (mipmaps)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, image[i]->components,
				image[i]->width, image[i]->height,
				image[i]->format, GL_UNSIGNED_BYTE, image[i]->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				//GL_LINEAR_MIPMAP_LINEAR);
				GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				//GL_LINEAR);
				GL_NEAREST);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, image[i]->components,
				image[i]->width, image[i]->height, 0,
				image[i]->format, GL_UNSIGNED_BYTE, image[i]->pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	gMaze = Maze(mazeX, mazeY);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	srand(time(NULL));
	std::cout << "Enter maze size as 'x y':     ";
	std::cin >> mazeX >> mazeY;
	screen_x = 1280;
	screen_y = 720;

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
