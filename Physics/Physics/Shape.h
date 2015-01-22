#pragma once

enum ShapeType{
	Square,
	Circle,
	Polygon,
	Mesh,
	Triangle,
	Other
};
struct Position{
	double x;
	double y;
};
struct Velocity{
	double dX;
	double dY;
};
struct Color{
	double red;
	double green;
	double blue;
};
class Shape{
	Shape();
	Shape(Position position);
	Shape(Position position, Velocity velocity);
	Shape(Position position, Velocity velocity, ShapeType shapeType, Color color);

	double GetX();
	double GetY();
	double GetDx();
	double GetDy();
	ShapeType GetType();
	virtual double GetDimensions() = 0;
	Position GetPosition();
	Velocity GetVelocity();
};