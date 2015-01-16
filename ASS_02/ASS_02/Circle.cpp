#include "Circle.h"
#include <cstdlib>
#include <vector>

Circle::Circle(){
	this->center = Point();
	this->color = Color();
	this->radius = 1.0;
}
Circle::Circle(Point center, double radius){
	this->center = center;
	this->radius = radius;
	this->color = Color();
}
Circle::Circle(Point center, double radius, Color color){
	this->center = center;
	this->radius = radius;
	this->color = color;
}

Circle::~Circle(){
	//nothing
}
void Circle::Update(){
	//check for bounce
	//check gravity
	//check air friction
	//check ball to ball collisions
	//Make a move function, then call it.
}
void Circle::Draw(){
	double centerX = this->center.GetX();
	double centerY = this->center.GetY();
	vector<double> velocity = this->center.GetVelocity();
	double radius = this->GetRadius();
	vector<double> colors = this->GetColor().GetColors();

	glColor3d(colors[0], colors[1], colors[2]);
	glBegin(GL_POLYGON);
	for (int i = 0; i<32; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = centerX + radius * cos(theta);
		double y = centerY + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}
void Circle::CheckBounce(){
	double radius = this->GetRadius();
	vector<double> velocity = this->GetCenterPoint().GetVelocity();
	double x = this->GetCenterPoint().GetX();
	double y = this->GetCenterPoint().GetY();
	//check if they will be offscreen if they are allowed to the next point.
	x += velocity[0];
	y += velocity[1];

	if (x - radius <= 0 && velocity[0] < 0){
		this->center.setVelocity(velocity[0] * -1.0, velocity[1]);
	}
	if (x + radius >= screen_x && velocity[0] > 0){
		this->center.setVelocity(velocity[0] * -1.0, velocity[1]);
	}
	if (y - radius <= 0 && velocity[1] < 0){
		this->center.setVelocity(velocity[0], velocity[1] * -1.0);
	}
	if (y + radius >= screen_y && velocity[1] > 0){
		this->center.setVelocity(velocity[0], velocity[1] * -1.0);
	}
}

Point Circle::GetCenterPoint(){
	return this->center;
}
Color Circle::GetColor(){
	return this->color;
}
double Circle::GetRadius(){
	return this->radius;
}

//this function is where velocity is obtained from
void Circle::setCenterPoint(Point other){
	this->center = other;
}
void Circle::setColor(Color other){
	this->color = other;
}
void Circle::setRadius(double other){
	this->radius = other;
}

void Circle::resetVelocity(){
	this->center.setVelocity(0.0, 0.0);
}