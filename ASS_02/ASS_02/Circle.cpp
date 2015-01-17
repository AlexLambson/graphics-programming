#include "Circle.h"
#include <cstdlib>
#include <vector>
#include <math.h>

Circle::Circle(){
	this->radius = 1.0;
}
Circle::Circle(Point center, double radius){
	this->shapePoint = center;
	this->radius = radius;
	this->shapeColor = Color();
}
Circle::Circle(Point center, double radius, Color color){
	this->shapePoint = center;
	this->radius = radius;
	this->shapeColor = color;
}

Circle::~Circle(){
	//nothing
}
void Circle::CheckCollision(Circle *other){
	bool collided = false;
	double myX, myY, myRadius, otherX, otherY, otherRadius, distanceX, distanceY, radii, myVx, myVy;
	myRadius = this->GetRadius();
	myVx = this->GetCenterPoint().GetVelocityX();
	myVy = this->GetCenterPoint().GetVelocityY();
	//add velocity to see where we WILL be
	myX = this->GetCenterPoint().GetX();// +myVx;
	myY = this->GetCenterPoint().GetY();// +myVy;
	//need their position
	otherX = other->GetCenterPoint().GetX();
	otherY = other->GetCenterPoint().GetY();
	otherRadius = other->GetRadius();
	if (myRadius == otherRadius && myX == otherX && myY == otherY){
		return;
	}
	myX += myVx;
	myY += myVy;
	distanceX = myX - otherX;
	distanceY = myY - otherY;
	radii = myRadius + otherRadius;

	if ((distanceX * distanceX) + (distanceY * distanceY) < radii * radii){
		this->shapePoint.setVelocity(myVx * -1.0, myVy * -1.0);
		other->Update();
	}

}
void Circle::CollisionHandler(){
	for each(Shape *shape in mShapes){
		Circle *circle = dynamic_cast<Circle *>(shape);
		this->CheckCollision(circle);
	}
}
void Circle::Update(){
	this->CheckBounce();
	this->CollisionHandler();
	//check gravity
	//check air friction
	//check ball to ball collisions

	//Make a move function, then call it.
	this->Move();

	this->Draw();
}
void Circle::Draw(){
	double centerX = this->shapePoint.GetX();
	double centerY = this->shapePoint.GetY();
	vector<double> velocity = this->shapePoint.GetVelocity();
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
void Circle::Move(){
	double vx = this->GetCenterPoint().GetVelocityX();
	double vy = this->GetCenterPoint().GetVelocityY();
	double x = this->shapePoint.GetX();
	double y = this->shapePoint.GetY();
	this->shapePoint.setX(x + vx);
	this->shapePoint.setY(y + vy);
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
		this->shapePoint.setVelocity(velocity[0] * -1.0, velocity[1]);
	}
	if (x + radius >= screen_x && velocity[0] > 0){
		this->shapePoint.setVelocity(velocity[0] * -1.0, velocity[1]);
	}
	if (y - radius <= 0 && velocity[1] < 0){
		this->shapePoint.setVelocity(velocity[0], velocity[1] * -1.0);
	}
	if (y + radius >= screen_y && velocity[1] > 0){
		this->shapePoint.setVelocity(velocity[0], velocity[1] * -1.0);
	}
}

Point Circle::GetCenterPoint(){
	return this->shapePoint;
}
Color Circle::GetColor(){
	return this->shapeColor;
}
double Circle::GetRadius(){
	return this->radius;
}

//this function is where velocity is obtained from
void Circle::setCenterPoint(Point other){
	this->shapePoint = other;
}
void Circle::setCenterPoint(double x, double y){
	this->shapePoint.setX(x);
	this->shapePoint.setY(y);
}
void Circle::setColor(Color other){
	this->shapeColor = other;
}
void Circle::setRadius(double other){
	this->radius = other;
}

void Circle::resetVelocity(){
	this->shapePoint.setVelocity(0.0, 0.0);
}