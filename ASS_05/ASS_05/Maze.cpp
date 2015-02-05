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
	this->setMazeSize(4, 4);
}
Maze::Maze(int sizeX, int sizeY){
	this->createMaze(sizeX, sizeY);
	this->setMazeSize(sizeX, sizeY);
}
void Maze::setMazeSize(int sizeX, int sizeY){
	this->mazeSize.sizeX = sizeX;
	this->mazeSize.sizeY = sizeY;
}
MazeSize Maze::getMazeSize(){
	return this->mazeSize;
}
void Maze::createMaze(int x, int y){
	this->mCells.resize(x);
	for (int i = 0; i < x; i++){
		this->mCells[i].resize(y);
		for (int j = 0; j < y; j++){
			this->mCells[i][j] = Cell();
			this->mCells[i][j].setPosition(i, j);
			this->mCells[i][j].visited = false;
		}
	}
	this->setMazeSize(x, y);
	this->removeWalls(0, 0);
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

	if (this->bottom){
		glVertex2i(x, y);
		glVertex2i(x + 1, y);
	}
	if (this->right){
		glVertex2i(x + 1, y);
		glVertex2i(x + 1, y + 1);
	}
	if (this->top){
		glVertex2i(x + 1, y + 1);
		glVertex2i(x, y + 1);
	}
	if (this->left){
		glVertex2i(x, y + 1);
		glVertex2i(x, y);
	}
	glEnd();
}
void Maze::Cell::setPosition(int x, int y){
	this->position.xPos = x;
	this->position.yPos = y;
}
void Maze::removeWalls(int x, int y){
	Cell * me = &this->mCells[x][y];
	me->visited = true;
	Unvisited unvisited = this->unvisitedNeighbors(x, y);
	while (unvisited.unvisitedNeighbor){
		int randomPick = rand() % unvisited.xPos.size();
		int newX, newY;
		newX = unvisited.xPos[randomPick];
		newY = unvisited.yPos[randomPick];
		Cell * other = &this->mCells[newX][newY];

		if (x < newX){
			me->right = false;
			other->left = false;
		}
		if (x > newX){
			me->left = false;
			other->right = false;
		}
		if (y < newY){
			me->top = false;
			other->bottom = false;
		}
		if (y > newY){
			me->bottom = false;
			other->top = false;
		}
		this->removeWalls(newX, newY);
		unvisited = this->unvisitedNeighbors(x, y);
	}
	return;
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
}
Unvisited Maze::unvisitedNeighbors(int myX, int myY){
	bool beginX = false, beginY = false, endX = false, endY = false;
	int mazeSizeX, mazeSizeY;
	mazeSizeX = this->getMazeSize().sizeX;
	mazeSizeY = this->getMazeSize().sizeY;
	Unvisited unvisited;

	if (myX + 1 >= mazeSizeX){
		endX = true;
	}
	if (myX - 1 < 0){
		beginX = true;
	}
	if (myY + 1 >= mazeSizeY){
		endY = true;
	}
	if (myY - 1 < 0){
		beginY = true;
	}
	if (!beginX && !this->mCells[myX - 1][myY].visited){
		unvisited.unvisitedNeighbor = true;
		unvisited.xPos.push_back( myX - 1);
		unvisited.yPos.push_back(myY);
	}
	if (!endX && !this->mCells[myX + 1][myY].visited){
		unvisited.unvisitedNeighbor = true;
		unvisited.xPos.push_back(myX + 1);
		unvisited.yPos.push_back(myY);
	}
	if (!beginY && !this->mCells[myX][myY - 1].visited){
		unvisited.unvisitedNeighbor = true;
		unvisited.xPos.push_back(myX);
		unvisited.yPos.push_back(myY - 1);
	}
	if (!endY && !this->mCells[myX][myY + 1].visited){
		unvisited.unvisitedNeighbor = true;
		unvisited.xPos.push_back(myX);
		unvisited.yPos.push_back(myY + 1);
	}
	return unvisited;
}