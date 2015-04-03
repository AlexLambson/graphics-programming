#pragma once

#include <cstdlib>
#include <vector> 
#include <glut.h>
//Tells rat's move() which key was pressed
namespace Key{
	enum Type{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
}
//pretty self explainatory
struct MazeSize{
	int sizeX, sizeY;
};
//index position of a cell
struct Position{
	Position();
	Position(int x, int y);
	int xPos, yPos;
};
//position in fractions for rats
struct PositionD{
	double xPos, yPos;
};
struct Unvisited{
	std::vector<Position> uPos;
	bool unvisitedNeighbor = false;
	void Push(int x, int y);
};
namespace Globals{
	extern double RatSize;
}
namespace Draw{
	void Circle(double x1, double y1, double radius);
	void Rectangle(double x1, double y1, double x2, double y2);
	void Triangle(double x1, double y1, double x2, double y2, double x3, double y3);
	void Text(double x, double y, char *string);
}