#include "Beizer.h"
Point2::Point2(){
	this->x = 0;
	this->y = 0;
}
Point2::Point2(float x, float y){
	this->x = x;
	this->y = y;
}
Beizer::Beizer(int iteration){
	this->mActive = false;
	this->mPoints.resize(3);
	this->mCircleRadius = 0.1;
	this->color.r = 0.3 * (1 + ((double)iteration / 2));
	this->color.g = 0.3 * (1 + ((double)iteration / 2));
	this->color.b = 0.5 * (1 + ((double)iteration / 2));
	if (this->color.r > 1) this->color.r = 0;
	if (this->color.g > 1) this->color.g = 0;
	if (this->color.b > 1) this->color.b = 0;
	double startx, starty;
	this->activeHandle = -1;
	startx = starty = 1.3 * (1 + ((double)iteration / 4));
	this->mPoints[0] = Point2(startx, starty);
	this->mPoints[1] = Point2(startx + 0.4, starty + 0.4);
	this->mPoints[2] = Point2(startx + 1.2, starty + 0.6);
	//this->mPoints[3] = Point2(startx + 1.6, starty - 0.8);
	this->iteration = iteration;
}

Point2 Beizer::Evaluate(float t){
	vector<Point2> p = this->mPoints;
	float pX = p[0].x*(1 - t)*(1 - t) + 2 * p[1].x*(1 - t)*t + p[2].x*t*t;
	float pY = p[0].y*(1 - t)*(1 - t) + 2 * p[1].y*(1 - t)*t + p[2].y*t*t;
	Point2 point = Point2(pX, pY);
	return point;
}

void Beizer::DrawCurve(int numberOfPoints){
	glColor3f(color.r, color.g, color.b);
	glLineWidth(2.5);
	glBegin(GL_LINES);

	float tIncrement = 1.0 / (float) numberOfPoints;
	float currentT = 0;
	Point2 prePoint = this->mPoints[0];
	Point2 currentPoint;
	for (int i = 0; i <= numberOfPoints; i++) {
		currentPoint = this->Evaluate(currentT);
		glVertex2f(prePoint.x, prePoint.y);
		glVertex2f(currentPoint.x, currentPoint.y);
		prePoint = currentPoint;
		currentT += tIncrement;
	}
	glEnd();
}
void DrawCircle(double x1, double y1, double radius, int segments)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i<segments; i++)
	{
		double theta = (double)i / 32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}
void Beizer::DrawControlPoints(){
	glLineWidth(1.0);
	for (int i = 0; i < this->mPoints.size(); i++){
		if (i == activeHandle || this->mActive){
			glColor3f(1.0, 0, 0);
		}
		else {
			double number1 = 0.2 * (1 + ((double)iteration / 2));
			double number2 = 0.4 * (1 + ((double)iteration / 3));
			double number3 = 0.3 * (1 + ((double)iteration));
			if (number1 > 0.7) number1 = 0.3;
			if (number1 > 0.9) number2 = 0.2;
			if (number1 > 0.6) number3 = 0.1;
			glColor3f(number1, number2, number3);
		}
		DrawCircle(this->mPoints[i].x, this->mPoints[i].y, this->mCircleRadius, 64);
	}
}
int Beizer::MouseHitHandle(int x, int y){
	for (int i = 0; i < this->mPoints.size(); i++){
		double pointX = this->mPoints[i].x;
		double pointY = this->mPoints[i].y;
		double dX = ((double)x / 100);
		double dY = ((double)y / 100);
		if (pow((dX - pointX), 2) + pow((dY - pointY), 2) <= pow(this->mCircleRadius, 2)){
			return i;
		}
	}
	return -1;
}
void Beizer::ActivateHandle(int i){
	if (i >= 0 && i < this->mPoints.size()){
		this->activeHandle = i;
	}
}
void Beizer::DeactivateHandle(){
	this->activeHandle = -1;
}
void Beizer::SetHandlePoint(int handle, int x, int y){
	Point2 temp = Point2((double)x/100, (double)y/100);
	this->mPoints[handle] = temp;
}
void Beizer::ActivateBeizer(){
	this->mActive = true;
}
void Beizer::DeactivateBeizer(){
	this->mActive = false;
}
bool Beizer::IsActive(){
	return this->mActive;
}
void Beizer::Move(double differenceX, double differenceY){
	differenceX = differenceX / 100;
	differenceY = differenceY / 100;
	for (int i = 0; i < this->mPoints.size(); i++){
		double currentX = this->mPoints[i].x;
		double currentY = this->mPoints[i].y;
		double newX = currentX + differenceX;
		double newY = currentY + differenceY;
		Point2 temp = Point2(newX, newY);
		this->mPoints[i] = temp;
	}
}
void Beizer::SetColor(MenuColor color){
	switch (color)
	{
	case MENU_RED:
		this->color.r = 1.0;
		this->color.g = 0.2;
		this->color.b = 0.3;
		break;
	case MENU_GREEN:
		this->color.r = 0.2;
		this->color.g = 0.7;
		this->color.b = 0.3;
		break;
	case MENU_BLUE:
		this->color.r = 0.2;
		this->color.g = 0.4;
		this->color.b = 0.9;
		break;
	case MENU_BLACK:
		this->color.r = 0;
		this->color.g = 0;
		this->color.b = 0;
		break;
	case MENU_PURPLE:
		this->color.r = 0.6;
		this->color.g = 0.0;
		this->color.b = 0.7;
		break;
	default:
		break;
	}
}