#include "Beizer.h"
Point2::Point2(){
	this->x = 0;
	this->y = 0;
}
Point2::Point2(float x, float y){
	this->x = x;
	this->y = y;
}
Beizer::Beizer(){
	this->mPoints.resize(4);
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

void Beizer::DrawControlPoints(){

}