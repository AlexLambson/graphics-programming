// (your name here)
// Chess animation starter kit.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;
#include "Piece.h"

int piece1ID = 3; // white queen pawn
int piece2ID = 19; //black queen pawn
int piece35ID = 11; //white queen
int piece4ID = 26; //black bishop
int piece6ID = 27; //black queen
int piece7ID = 28; //black king

// Global Variables
// Some colors you can use, or make your own and add them
// here and in graphics.h
GLfloat redMaterial[] = { 0.7, 0.1, 0.2, 1.0 };
GLfloat greenMaterial[] = { 0.1, 0.7, 0.4, 1.0 };
GLfloat brightGreenMaterial[] = { 0.1, 0.9, 0.1, 1.0 };
GLfloat blueMaterial[] = { 0.1, 0.2, 0.7, 1.0 };
GLfloat whiteMaterial[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat blackMaterial[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat grayMaterial[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat creamMaterial[] = {1.0, 0.8, 0.7, 1.0};
GLfloat brownMaterial[] = { 0.7274, 0.5215, 0.3764 };
unsigned int BOARD_GL_ID = 201;
int CELL_SIZE = 1000;
int BOARD_HEIGHT = CELL_SIZE / 4;
double screen_x = 1280;
double screen_y = 720;
Board gBoard = Board();
clock_t startTime = clock();
GLuint part;

//white is first 16. order goes pawns first
Piece* pieces = new Piece[32];
//enum pieceNames{ PAWN = 100, ROOK, KNIGHT, BISHOP, QUEEN, KING };
unsigned int backRow[] = { ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK};

// Outputs a string of text at the specified location.
void text_output(double x, double y, char *string)
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

// Given the three triangle points x[0],y[0],z[0],
//		x[1],y[1],z[1], and x[2],y[2],z[2],
//		Finds the normal vector n[0], n[1], n[2].
void FindTriangleNormal(double x[], double y[], double z[], double n[])
{
	// Convert the 3 input points to 2 vectors, v1 and v2.
	double v1[3], v2[3];
	v1[0] = x[1] - x[0];
	v1[1] = y[1] - y[0];
	v1[2] = z[1] - z[0];
	v2[0] = x[2] - x[0];
	v2[1] = y[2] - y[0];
	v2[2] = z[2] - z[0];
	
	// Take the cross product of v1 and v2, to find the vector perpendicular to both.
	n[0] = v1[1]*v2[2] - v1[2]*v2[1];
	n[1] = -(v1[0]*v2[2] - v1[2]*v2[0]);
	n[2] = v1[0]*v2[1] - v1[1]*v2[0];

	double size = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);
	n[0] /= -size;
	n[1] /= -size;
	n[2] /= -size;
}
void RatioSet(double Time, double Time1, double Time2, double &value, double startValue, double endValue){
	double ratio = (Time - Time1) / (Time2 - Time1);
	if (ratio < 0)
		ratio = 0;
	if (ratio > 1)
		ratio = 1;
	value = startValue + ratio*(endValue - startValue);
}
// Loads the given data file and draws it at its default position.
// Call glTranslate before calling this to get it in the right place.
void DrawPiece(char filename[])
{
	// Try to open the given file.
	char buffer[200];
	ifstream in(filename);
	if(!in)
	{
		cerr << "Error. Could not open " << filename << endl;
		exit(1);
	}

	double x[100], y[100], z[100]; // stores a single polygon up to 100 vertices.
	int done = false;
	int verts = 0; // vertices in the current polygon
	int polygons = 0; // total polygons in this file.
	do
	{
		in.getline(buffer, 200); // get one line (point) from the file.
		int count = sscanf(buffer, "%lf, %lf, %lf", &(x[verts]), &(y[verts]), &(z[verts]));
		done = in.eof();
		if(!done)
		{
			if(count == 3) // if this line had an x,y,z point.
			{
				verts++;
			}
			else // the line was empty. Finish current polygon and start a new one.
			{
				if(verts>=3)
				{
					glBegin(GL_POLYGON);
					double n[3];
					FindTriangleNormal(x, y, z, n);
					glNormal3dv(n);
					for(int i=0; i<verts; i++)
					{
						glVertex3d(x[i], y[i], z[i]);
					}
					glEnd(); // end previous polygon
					polygons++;
					verts = 0;
				}
			}
		}
	}
	while(!done);

	if(verts>0)
	{
		cerr << "Error. Extra vertices in file " << filename << endl;
		exit(1);
	}

}
// NOTE: Y is the UP direction for the chess pieces.
double eye[3] = { -2000, 4000, 4000 }; // pick a nice vantage point.
double at[3] = { 4500, 1000, 4000 };
void animate(){
	clock_t endTime = clock();
	double Time = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	//die animation example
	/*glPushMatrix();
	double rotation = 0;
	double y = BOARD_HEIGHT;
	RatioSet(Time, 1, 3, rotation, 0, 180);
	RatioSet(Time, 3, 6, y, BOARD_HEIGHT, -30000);
	pieces[0].setRotation(rotation, pieces[0].getRotation().y, pieces[0].getRotation().z);
	pieces[0].setPosition(pieces[0].getPosition().x, y, pieces[0].getPosition().z);
	glPopMatrix();*/
	Position position;
	double pZ;
	double pX;
	if (Time <= 2.5){
		position = pieces[piece1ID].getPosition();
		double static zStart = position.z;
		pZ = 0;
		RatioSet(Time, 1, 2, pZ, zStart, zStart + (2 * CELL_SIZE));
		pieces[piece1ID].setPosition(position.x, position.y, pZ);
	}
	if (Time >= 3 && Time <= 4.5){
		position = pieces[piece2ID].getPosition();
		double static zStart2 = position.z;
		pZ = 0;
		RatioSet(Time, 3, 4, pZ, zStart2, zStart2 - (2 * CELL_SIZE));
		pieces[piece2ID].setPosition(position.x, position.y, pZ);
	}
	//white queen
	if ((Time >= 4 && Time <= 5.5) || (Time >= 8 && Time <= 9.5) || (Time >= 17 && Time <= 18.5)){
		position = pieces[piece35ID].getPosition();
		double static zStart3 = position.z;
		double zStart5 = zStart3 + (2 * CELL_SIZE);
		double zStart7 = zStart5 + (2 * CELL_SIZE);
		double queenZ = 0;
		double static xStart5 = position.x;
		double xStart7 = xStart5 + (2 * CELL_SIZE);
		double pX = 0;
		//second move
		RatioSet(Time, 8, 9, queenZ, zStart5, zStart5 + (2 * CELL_SIZE));
		RatioSet(Time, 8, 9, pX, xStart5, xStart5 + (2 * CELL_SIZE));
		//first move
		if (Time < 8){
			RatioSet(Time, 4, 5, queenZ, zStart3, zStart3 + (2 * CELL_SIZE));
		}
		if (Time >= 17){
			RatioSet(Time, 17, 18, queenZ, zStart7, zStart7 + (3 * CELL_SIZE));
			RatioSet(Time, 17, 18, pX, xStart7, xStart7 - (3 * CELL_SIZE));
		}
		pieces[piece35ID].setPosition(pX, position.y, queenZ);
	}
	//black bishop
	if ((Time >= 6 && Time <= 7.5) || (Time >= 8 && Time <= 14.5)){
		position = pieces[piece4ID].getPosition();
		double static zStart4 = position.z;
		double static xStart4 = position.x;
		pZ = 0;
		pX = 0;
		double bishopY = BOARD_HEIGHT;
		RatioSet(Time, 6, 7, pZ, zStart4, zStart4 - (3 * CELL_SIZE));
		RatioSet(Time, 6, 7, pX, xStart4, xStart4 + (3 * CELL_SIZE));
		if (Time >= 8){
			double rotationZ = 0;
			double rotationY = 0;
			RatioSet(Time, 8.5, 12, rotationZ, 0, 180);
			RatioSet(Time, 8.5, 11, rotationY, 0, 360);
			RatioSet(Time, 12, 14, bishopY, BOARD_HEIGHT, -30 * CELL_SIZE);
			pieces[piece4ID].setRotation(0, rotationY, rotationZ);
		}
		pieces[piece4ID].setPosition(pX, bishopY, pZ);
	}
	//black queen
	if (Time >= 14 && Time <= 17.5){
		position = pieces[piece6ID].getPosition();
		double static zStart6 = position.z;
		pZ = 0;
		RatioSet(Time, 14.5, 16.5, pZ, zStart6, zStart6 - (2 * CELL_SIZE));
		pieces[piece6ID].setPosition(position.x, position.y, pZ);
	}
	//black king
	if (Time >= 18 && Time <= 19.5){
		double kingY = BOARD_HEIGHT;
		position = pieces[piece7ID].getPosition();
		if (Time >= 18){
			RatioSet(Time, 18, 18.5, kingY, BOARD_HEIGHT, BOARD_HEIGHT + (CELL_SIZE / 2));
		}
		if (Time >= 18.5){
			RatioSet(Time, 18.5, 19, kingY, BOARD_HEIGHT + (CELL_SIZE / 2), BOARD_HEIGHT);
		}
		pieces[piece7ID].setPosition(position.x, kingY, position.z);
	}

	//camera
	if (Time >= 10 && Time <= 15.5){
		double camera = 0;
		RatioSet(Time, 10, 12, camera, 4000, -1000);
		if (Time >= 10.5){
			at[1] = pieces[piece4ID].getPosition().y;
		}
		if (Time >= 13){
			double atY = at[1];
			double static startCY = at[1];
			RatioSet(Time, 13, 15, atY, startCY, 1000);
			RatioSet(Time, 13, 15, camera, -1000, 4000);
			at[1] = atY;
		}
		eye[1] = camera;
	}
}
//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	clock_t endTime = clock();
	double Time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	gluLookAt(eye[0], eye[1], eye[2],  at[0], at[1], at[2],  0,1,0); // Y is up!

	// Set the color for one side (white), and draw its 16 pieces.
	/*GLfloat mat_amb_diff1[] = {0.8, 0.9, 0.5, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff1);

	glPushMatrix();
	glTranslatef(1000, BOARD_HEIGHT, 1000);
	DrawPiece("ROOK.POL");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2000, BOARD_HEIGHT, 1000);
	DrawPiece("KNIGHT.POL");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3000, BOARD_HEIGHT, 1000);
	DrawPiece("BISHOP.POL");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4000, BOARD_HEIGHT, 1000);
	DrawPiece("KING.POL");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5000, BOARD_HEIGHT, 1000);
	DrawPiece("QUEEN.POL");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6000, BOARD_HEIGHT, 1000);
	DrawPiece("BISHOP.POL");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7000, BOARD_HEIGHT, 1000);
	DrawPiece("KNIGHT.POL");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8000, BOARD_HEIGHT, 1000);
	DrawPiece("ROOK.POL");
	glPopMatrix();*/

	/*for (int x = 1000; x <= 8000; x += 1000)
	{
		glPushMatrix();
		glTranslatef(x, BOARD_HEIGHT, 2000);
		DrawPiece("PAWN.POL");
		glPopMatrix();
	}*/
	// Set the color for one side (black), and draw its 16 pieces.
	/*GLfloat mat_amb_diff2[] = {0.1, 0.5, 0.8, 1.0};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blackMaterial);

	glPushMatrix();
	glTranslatef(4000, BOARD_HEIGHT, 8000);
	DrawPiece("KING.POL");
	glPopMatrix();

	for(int x=1000; x<=8000; x+=1000)
	{
		glPushMatrix();
		glTranslatef(x, BOARD_HEIGHT, 7000);
		DrawPiece("PAWN.POL");
		glPopMatrix();
	}*/
	animate();
	//gBoard.Draw();
	glCallList(BOARD_GL_ID);
	for (int i = 0; i < 32; i++){
		pieces[i].Draw();
	}
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
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}



void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble) w/(GLdouble) h;
	gluPerspective( 
	/* field of view in degree */ 75.0,
	/* aspect ratio */ aspectRatio,
	/* Z near */ 100, /* Z far */ 30000.0);
	glMatrixMode(GL_MODELVIEW);
}

// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	SetPerspectiveView(w,h);

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
void MakePieces(){
	
	glNewList(PAWN, GL_COMPILE);
	DrawPiece("PAWN.POL");
	glEndList();
	glNewList(ROOK, GL_COMPILE);
	DrawPiece("ROOK.POL");
	glEndList();
	glNewList(KNIGHT, GL_COMPILE);
	DrawPiece("KNIGHT.POL");
	glEndList();
	glNewList(BISHOP, GL_COMPILE);
	DrawPiece("BISHOP.POL");
	glEndList();
	glNewList(KING, GL_COMPILE);
	DrawPiece("KING.POL");
	glEndList();
	glNewList(QUEEN, GL_COMPILE);
	DrawPiece("QUEEN.POL");
	glEndList();
	glNewList(BOARD_GL_ID, GL_COMPILE);
	gBoard.Draw();
	glEndList();

	int piecesPosition = 0;
	for (int x = CELL_SIZE; x <= CELL_SIZE * 8; x += CELL_SIZE)
	{
		Piece pawn = Piece(x, BOARD_HEIGHT, CELL_SIZE * 2, PAWN, RED, part);
		pieces[piecesPosition] = pawn;
		piecesPosition++;
	}
	for (int x = CELL_SIZE; x <= CELL_SIZE * 8; x += CELL_SIZE){
		Piece piece = Piece(x, BOARD_HEIGHT, CELL_SIZE, backRow[piecesPosition - 8], RED, part);
		pieces[piecesPosition] = piece;
		piecesPosition++;
	}
	for (int x = CELL_SIZE; x <= CELL_SIZE * 8; x += CELL_SIZE)
	{
		Piece pawn = Piece(x, BOARD_HEIGHT, CELL_SIZE * 7, PAWN, BLUE, part);
		pieces[piecesPosition] = pawn;
		piecesPosition++;
	}
	for (int x = CELL_SIZE; x <= CELL_SIZE * 8; x += CELL_SIZE){
		Piece piece = Piece(x, BOARD_HEIGHT, CELL_SIZE * 8, backRow[piecesPosition - 24], BLUE, part);
		pieces[piecesPosition] = piece;
		piecesPosition++;
	}

}
// Your initialization code goes here.
void InitializeMyStuff()
{
	// set material's specular properties
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess[] = {50.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// set light properties
	GLfloat light_position[] = {eye[0], eye[1], eye[2],1};
	GLfloat white_light[] = {1,1,1,1};
	GLfloat low_light[] = {.3,.3,.3,1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // position first light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light); // specify first light's color
	glLightfv(GL_LIGHT0, GL_SPECULAR, low_light);
	glClearColor(0.4f, 0.5f, 0.7f, 0.4f);

	glEnable(GL_DEPTH_TEST); // turn on depth buffering
	glEnable(GL_LIGHTING);	// enable general lighting
	glEnable(GL_LIGHT0);	// enable the first light.

	MakePieces();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(10, 10);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("Shapes");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glClearColor(1,1,1,1);	
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
