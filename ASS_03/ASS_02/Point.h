#ifndef _POINT_H_
#define _POINT_H_

#include <vector>

using namespace std;

class Point{
public:
	Point();
	Point(const double dX, const double dY);
	
	Point &operator=(Point &other);
	bool operator==(Point &other);
	bool operator!=(Point &other);

	void setPoint(const double dX, double dY);
	void setX(const double x);
	void setY(const double y);
	void setVelocity(const double vX, const double vY);
	void setVelocityX(const double vX);
	void setVelocityY(const double vY);

	vector<double> GetPoint();
	double GetX();
	double GetY();
	vector<double> GetVelocity();
	double GetVelocityX();
	double GetVelocityY(); 
protected:
	double positionX, positionY, velocityX, velocityY;
};

#endif