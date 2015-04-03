#pragma once
#include "Structs.h"
#include <glut.h>
class Rat
{
public:
	Rat();
	Rat(double cellX, double cellY);
	void Draw();
	//move the rat this many points
	void Move(Key::Type key);
private:
	PositionD mPosition;
	double mRotation;
	double mSize;
};
