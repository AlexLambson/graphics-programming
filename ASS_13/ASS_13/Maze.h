#pragma once
#include "Structs.h"
#include <random>
#include <cstdlib>
#include "tga.h"
using namespace std;
#include <glut.h>
class Maze;
class Rat
{
public:
	Rat();
	Rat(double cellX, double cellY);
	void Draw();
	Position GetIndex();
	bool CanMove(double dx, double dy, CellWalls walls);
	//move the rat this many points
	void HandleKey(Key::Type key, CellWalls walls);
	void Move(CellWalls walls, bool back = false);
	double GetX();
	double GetY();
	double GetZ();
	double GetRotation();
	double GetDX();
	double GetDY();
private:
	PositionD mPosition;
	double mRotation;
	double mSize;
};
class Maze{
	public:
		Maze();
		Maze(int sizeX, int sizeY);
		void Draw(GLuint * texName); //draw all cells. tell cells to draw themselves
		void createMaze(int x, int y);
		void removeWalls(int x, int y); //initially 0, 0.
		//get the walls for the rat
		CellWalls GetCellWalls(Position position);
		MazeSize getMazeSize();
		Rat rat;
	private:
		void setMazeSize(int sizeX, int sizeY);
		Unvisited unvisitedNeighbors(int myX, int myY);
		MazeSize mazeSize;
		bool startCell, endCell; 
		class Cell{
			public:
				Cell();
				void setPosition(int x, int y);
				void Draw(int mazeX, int mazeY, GLuint * texname);
				//draws from bottom left to top right.
				//make all true in constucter
				//wall is on or off
				CellWalls walls;
				bool visited;
				Position position;
				int r, g, b;
		};
		std::vector<std::vector<Cell>> mCells;
};
