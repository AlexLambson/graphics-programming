#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Point.h"
#include "Color.h"

#include <cmath>
#ifdef _WIN32
	#include "glut.h"
#else
	#ifdef __APPLE__
		#include <GLUT/glut.h>
	#else
		#include <GL/glut.h>
	#endif
#endif

class Shape{
public:
	Shape();
	Shape(Point &point, Color &color);
	Shape(Point &point);
	virtual ~Shape();
	virtual void Draw() = 0;
	virtual void Update() = 0;

	enum ShapeType{
		Circle
	};


	ShapeType shapeType;

	Color shapeColor;
	Point shapePoint;
};

#endif