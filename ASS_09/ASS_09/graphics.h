#include "glut.h"

void text_output(double x, double y, char *string);
void DrawCircle(double x1, double y1, double radius);
void DrawRectangle(double x1, double y1, double x2, double y2);
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void FindTriangleNormal(double x[], double y[], double z[], double n[]);
void DrawPiece(char filename[]);


// "Prototypes" of some color variables defined in graphics.cpp
extern GLfloat redMaterial[];
extern GLfloat greenMaterial[];
extern GLfloat brightGreenMaterial[];
extern GLfloat blueMaterial[];
extern GLfloat whiteMaterial[];
extern GLfloat blackMaterial[];
extern GLfloat grayMaterial[];
extern GLfloat creamMaterial[];
extern GLfloat brownMaterial[];
extern int BOARD_HEIGHT;
extern int CELL_SIZE;