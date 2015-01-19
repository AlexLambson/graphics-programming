#pragma once 

#include <cstdlib>
#include <vector>
#include "Shape.h"
#include <set>

using namespace std;

class Physics{
public:
	Physics();

	void HandleCollisions();
	void ApplyAirFriction();
	void ApplyGravity();
	void UpdateObjects();
	void FindMouseCollisions(int mouseX, int mouseY, double screenX, double screenY);

	vector<Shape *> Collidables;

	double Gravity = 0.0001;
	double BounceFriction = 0.85;
	double AirFriction = 0.99999999999;
};