#include "Maze.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <time.h>
Rat::Rat(){
	//start rat in the center of cell 0,0
	this->mPosition.xPos = 0.5;
	this->mPosition.yPos = 0.5;
	this->mPosition.zPos = 0.3;
	this->mSize = Globals::RatSize;
	this->mRotation = 0.0;
}
Rat::Rat(double cellX, double cellY){
	this->mPosition.xPos = cellX;
	this->mPosition.yPos = cellY;
	this->mPosition.zPos = .3;
	this->mSize = Globals::RatSize;
	this->mRotation = 0.0;
}
void Rat::Draw(){
	//glpushmatrix
	//gltranslated(x, y, 0)
	//glrotated(mrotation, 0, 0, 1)
	//draw rat at origin
	double x1, y1, x2, y2;
	this->mPosition.zPos = (sin(clock() * 0.001)+1.4)/4;
	//rat is a square that is .4 world units width and height
	//to get bottom left corner for drawing, subtract 
	x1 = this->mPosition.xPos - this->mSize / 2;
	y1 = this->mPosition.yPos - this->mSize / 2;
	x2 = x1 + this->mSize;
	y2 = y1 + this->mSize;	
	glPushMatrix();
	glTranslated(this->mPosition.xPos, this->mPosition.yPos, this->mPosition.zPos);
	glRotated(this->mRotation, 0, 0, 1);
	glScalef(0.5, 0.5, 0.5);
	glColor3ub(255,45,75);
	glutSolidCube(0.5);
	//Draw::Indicator(this->mPosition.xPos, this->mPosition.yPos, 0.4);
	glPopMatrix();

	glColor3ub(128, 128, 128);
	glPushMatrix();

	const float dirX = GetDX() * 2.3;
	const float dirY = GetDY() * 2.3;

	glTranslated(this->mPosition.xPos - dirX, this->mPosition.yPos - dirY, this->mPosition.zPos);
	glRotated(this->mRotation, 0, 0, 1);
	glScaled(1.2, .6, .7);
	glutSolidCube(0.5);
	glPopMatrix();
	/*
	glRotated(this->mRotation, 0, 0, 1);
	glTranslated(this->mPosition.xPos, this->mPosition.yPos, 0.1);
	glScalef(0.5, 0.5, 0.5);
	glColor3ub(0, 0, 0);
	glutSolidCube(0.5);
	glPopMatrix();
	*/
}
bool Rat::CanMove(double dx, double dy, CellWalls walls){
	Position index = this->GetIndex();
	int xIndex = index.xPos;
	int yIndex = index.yPos;
	double offsetX = dx - xIndex;
	double offsetY = dy - yIndex;
	if (offsetX - this->mSize / 2 < -0.00004 && walls.left){
		return false;
	}
	if (offsetX + this->mSize / 2 > 1.00004 && walls.right){
		return false;
	}
	if (offsetY - this->mSize / 2 < 0 && walls.bottom){
		return false;
	}
	if (offsetY + this->mSize / 2 > 1 && walls.top){
		return false;
	}
	return true;
}
/*void Rat::Move(Key::Type key, CellWalls walls){
	PositionD projectedPosition = this->mPosition;
	Position index = this->GetIndex();
	double xPos = (double)index.xPos;
	double yPos = (double)index.yPos;

	switch (key){
		case Key::UP:
			projectedPosition.yPos += Globals::RatCellsPerSecond;
			if (!walls.top){
				this->mPosition = projectedPosition;
			}
			else if ((yPos + 1) - projectedPosition.yPos > this->mSize / 2){
				this->mPosition = projectedPosition;
			}
			break;
		case Key::DOWN:
			projectedPosition.yPos -= Globals::RatCellsPerSecond;
			if (!walls.bottom){
				this->mPosition = projectedPosition;
			}
			else if (projectedPosition.yPos - yPos > this->mSize / 2){
				this->mPosition = projectedPosition;
			}
			break;
		case Key::RIGHT:
			projectedPosition.xPos += Globals::RatCellsPerSecond;
			break;
		case Key::LEFT:
			projectedPosition.xPos -= Globals::RatCellsPerSecond;
			break;
		default:
			return;
	}
	if (this->CanMove(projectedPosition, walls)){
		this->mPosition = projectedPosition;
	}
}*/
void Rat::HandleKey(Key::Type key, CellWalls walls){
	switch (key){
	case Key::UP:
		this->Move(walls);
		break;
	case Key::LEFT:
		this->mRotation += Globals::RatRotationSpeed;
		break;
	case Key::RIGHT:
		this->mRotation -= Globals::RatRotationSpeed;
		break;
	case Key::DOWN:
		this->Move(walls, true);
		break;
	default:
		break;
	}
	return;
}
void Rat::Move(CellWalls walls, bool back){
	double radians = this->mRotation * M_PI / 180.0;
	double dx = cos(radians) * Globals::RatCellsPerSecond;
	double dy = sin(radians) * Globals::RatCellsPerSecond;
	if (back){
		dx *= -1.0;
		dy *= -1.0;
	}
	double newX = dx + this->mPosition.xPos;
	double newY = dy + this->mPosition.yPos;
	if (this->CanMove(newX, newY, walls)){
		this->mPosition.xPos = newX;
		this->mPosition.yPos = newY;
	}
	else if (this->CanMove(this->mPosition.xPos, newY, walls)){
		this->mPosition.yPos = newY;
	}
	else if (this->CanMove(newX, this->mPosition.yPos, walls)){
		this->mPosition.xPos = newX;
	}
}
Position Rat::GetIndex(){
	Position index;
	index.xPos = (int)this->mPosition.xPos;
	index.yPos = (int)this->mPosition.yPos;
	return index;
}
double Rat::GetX(){
	return this->mPosition.xPos;
}
double Rat::GetY(){
	return this->mPosition.yPos;
}
double Rat::GetZ(){
	return this->mPosition.zPos;
}
double Rat::GetRotation(){
	return this->mRotation;
}
double Rat::GetDX(){
	double radians = this->mRotation * M_PI / 180.0;
	double dx = cos(radians) * Globals::RatCellsPerSecond;
	return dx;
}
double Rat::GetDY(){
	double radians = this->mRotation * M_PI / 180.0;
	double dy = sin(radians) * Globals::RatCellsPerSecond;
	return dy;
}