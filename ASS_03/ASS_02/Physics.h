#pragma once 

#include <cstdlib>
#include <vector>
#include "Shape.h"
#include <set>
#include <math.h>

using namespace std;

class Physics{
public:
	Physics();

	void HandleCollisions();
	void ApplyAirFriction();
	void ApplyGravity();
	void UpdateObjects();
	void FindMouseCollisions(int mouseX, int mouseY, double screenX, double screenY);
	void Collide(int p1, int p2);

	vector<Shape *> Collidables;

	double Gravity = 0.000001;
	double AirFriction = 0.99999999999;
};