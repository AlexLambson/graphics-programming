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
	this->mPoints.resize(4);
	this->mCircleRadius = 0.1;
	this->color.r = 0.3;
	this->color.g = 0.3;
	this->color.b = 0.5;
	double startx, starty;
	startx = starty = 3.0 * (1 + (double) (iteration / 10));
	this->mPoints[0] = Point2(startx, starty);
	this->mPoints[1] = Point2(startx + 0.8, starty + 0.8);
	this->mPoints[2] = Point2(startx + 2.4, starty + 1.2);
	this->mPoints[3] = Point2(startx + 3.2, starty - 1.6);
}

Point2 Beizer::Evaluate(float t){
	vector<Point2> p = this->mPoints;
	float pX = p[0].x*(1 - t)*(1 - t)*(1 - t) + 3 * p[1].x*(1 - t)*(1 - t)*t + 3 * p[2].x*(1 - t)*t*t + p[3].x*t*t*t;
	float pY = p[0].y*(1 - t)*(1 - t)*(1 - t) + 3 * p[1].y*(1 - t)*(1 - t)*t + 3 * p[2].y*(1 - t)*t*t + p[3].y*t*t*t;
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
	glColor3f(color.r + 0.3, color.g + 0.1, color.b - 0.1);
	glLineWidth(1.0);
	for (int i = 0; i < this->mPoints.size(); i++){
		DrawCircle(this->mPoints[i].x, this->mPoints[i].y, this->mCircleRadius, 64);
	}
}