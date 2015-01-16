#ifndef _circle_head_
#define _circle_head_

#include "Shape.h"
#include "Globals.h"

class Circle : public Shape{
public:
	Circle();
	Circle(Point center, double radius);
	Circle(Point center, double radius, Color color);

	virtual ~Circle();
	void Draw();
	void Update();
	void CheckBounce();
	void Move();

	Point GetCenterPoint();
	Color GetColor();
	double GetRadius();

	//this function is where velocity is obtained from
	void setCenterPoint(Point other);
	void setColor(Color other);
	void setRadius(double other);

	void resetVelocity();

private:
	Point center;
	Color color;
	double radius;
};

#endif