#include <cstdlib>
#include <vector>
#include <random>
#include <glut.h>


struct MazeSize{
	int sizeX, sizeY;
};
struct Position{
	int xPos, yPos;
};
struct Unvisited{
	std::vector<int> xPos;
	std::vector<int> yPos;
	bool unvisitedNeighbor = false;
};
class Maze{
	public:
		Maze();
		Maze(int sizeX, int sizeY);
		void Draw(); //draw all cells. tell cells to draw themselves
		void createMaze(int x, int y);
		void removeWalls(int x, int y); //initially 0, 0.
		MazeSize getMazeSize();
		/*
		marks cell visited;
		mcells[i][j].visited = true;

		while I have an unvisited neghbor{
			randomly pick an unvisited neighbor;
			return if no neighbor is open;
			if right{
				remove my right wall;
				remove neigbors left wall;
				removeWalls(my neigbor); (x+1, y)
			}
		}
		*/
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