#include "Rat.h"

Rat::Rat(){
	//start rat in the center of cell 0,0
	this->mPosition.xPos = 0.5;
	this->mPosition.yPos = 0.5;
	this->mSize = Globals::RatSize;
}
Rat::Rat(double cellX, double cellY){
	this->mPosition.xPos = cellX;
	this->mPosition.yPos = cellY;
	this->mSize = Globals::RatSize;
}
void Rat::Draw(){
	double x1, y1, x2, y2;
	//rat is a square that is .4 world units width and height
	//to get bottom left corner for drawing, subtract 
	x1 = this->mPosition.xPos - this->mSize / 2;
	y1 = this->mPosition.yPos - this->mSize / 2;
	x2 = x1 + this->mSize;
	y2 = y1 + this->mSize;
	Draw::Rectangle(x1, y1, x2, y2);
}
void Rat::Move(Key::Type key){
	switch (key){
		case Key::UP:
			this->mPosition.yPos += 1.0;
			break;
		case Key::DOWN:
			this->mPosition.yPos -= 1.0;
			break;
		case Key::RIGHT:
			this->mPosition.xPos += 1.0;
			break;
		case Key::LEFT:
			this->mPosition.xPos -= 1.0;
			break;
		default:
			return;
	}
}