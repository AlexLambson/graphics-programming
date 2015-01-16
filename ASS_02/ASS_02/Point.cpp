#include "Point.h"

Point::Point(){
	this->setPoint(0.0, 0.0);
	this->setVelocity(0.0, 0.0);
}
Point::Point(const double dX, const double dY){
	this->setPoint(dX, dY);
	this->setVelocity(0.0, 0.0);
}
Point &Point::operator=(Point &other){
	this->setPoint(other.GetX(), other.GetY());
	this->setVelocity(other.GetVelocityX(), other.GetVelocityY());
	return *this;
}
bool Point::operator==(Point &other){
	return this->GetX() == other.GetX() && this->GetY() == other.GetY();
}
bool Point::operator!=(Point &other){
	return this->GetX() != other.GetX() || this->GetY() != other.GetY();
}
void Point::setPoint(const double dX, double dY){
	this->setX(dX);
	this->setY(dY);
}
void Point::setX(const double x){
	this->positionX = x;
}
void Point::setY(const double y){
	this->positionY = y;
}
void Point::setVelocity(const double vX, const double vY){
	this->setVelocityX(vX);
	this->setVelocityY(vY);
}
void Point::setVelocityX(const double vX){
	this->velocityX = vX;
}
void Point::setVelocityY(const double vY){
	this->velocityY = vY;
}
vector<double> Point::GetPoint(){
	vector<double> point(2);
	point[0] = this->GetX();
	point[1] = this->GetY();
	return point;
}
double Point::GetX(){
	return this->positionX;
}
double Point::GetY(){
	return this->positionY;
}
vector<double> Point::GetVelocity(){
	vector<double> point(2);
	point[0] = this->GetVelocityX();
	point[1] = this->GetVelocityY();
	return point;
}
double Point::GetVelocityX(){
	return this->velocityX;
}
double Point::GetVelocityY(){
	return this->velocityY;
}