#include "Shape.h"
#include "Point.h"


Shape::Shape(){
	this->shapeColor = Color();
	this->shapePoint = Point();
}
Shape::Shape(Point &point, Color &color){
	this->shapeColor = color;
	this->shapePoint = point;
}
Shape::Shape(Point &point){
	this->shapeColor = Color();
	this->shapePoint = point;
}
Shape::~Shape(){
	//nothing
}
