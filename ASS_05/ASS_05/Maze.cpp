#include "Maze.h"
using namespace std;
Maze::Cell::Cell(){
	left = true;
	top = true;
	bottom = true;
	right = true;
	visited = false;
}
Maze::Maze(){
	this->createMaze(4, 4);
}
Maze::Maze(int sizeX, int sizeY){
	this->createMaze(sizeX, sizeY);
}
void Maze::createMaze(int x, int y){
	this->mCells.resize(x);
	for (int i = 0; i < x; i++){
		this->mCells[i].resize(y);
		for (int j = 0; j < y; j++){
			this->mCells[i][j] = Cell();
			this->mCells[i][j].setPosition(i, j);
		}
	}
}
void Maze::Draw(){
	int xSize = this->mCells.size();
	for (int i = 0; i < xSize; i++){
		int ySize = this->mCells[i].size();
		for (int j = 0; j < ySize; j++){
			this->mCells[i][j].Draw();
		}
	}
}
void Maze::Cell::Draw(){

	int x, y;
	x = this->position.xPos;
	y = this->position.yPos;

	glBegin(GL_LINES);

	glVertex2i(x, y);
	glVertex2i(x + 1, y);

	glVertex2i(x + 1, y);
	glVertex2i(x + 1, y + 1);

	glVertex2i(x + 1, y + 1);
	glVertex2i(x, y + 1);

	glVertex2i(x, y + 1);
	glVertex2i(x, y);

	glEnd();
}
void Maze::Cell::setPosition(int x, int y){
	this->position.xPos = x;
	this->position.yPos = y;
}