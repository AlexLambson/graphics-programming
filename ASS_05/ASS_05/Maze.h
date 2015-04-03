#pragma once
#include "Structs.h"
#include "Rat.h"
#include <random>
#include <glut.h>

class Maze{
	public:
		Maze();
		Maze(int sizeX, int sizeY);
		void Draw(); //draw all cells. tell cells to draw themselves
		void createMaze(int x, int y);
		void removeWalls(int x, int y); //initially 0, 0.
		MazeSize getMazeSize();
		Rat rat = Rat();
	private:
		void setMazeSize(int sizeX, int sizeY);
		Unvisited unvisitedNeighbors(int myX, int myY);
		MazeSize mazeSize;
		bool startCell, endCell; 
		class Cell{
			public:
				Cell();
				void setPosition(int x, int y);
				void Draw();
				//draws from bottom left to top right.
				//make all true in constucter
				//wall is on or off
				bool left, bottom, right, top;
				bool visited;
				Position position;
		};
		std::vector<std::vector<Cell>> mCells;
};