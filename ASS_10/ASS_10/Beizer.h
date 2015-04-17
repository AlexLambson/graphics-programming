#include <vector>
#include <glut.h>
using namespace std;

struct RGB {
	float r, g, b;
};

class Point2 {
public:
	Point2();
	Point2(float x, float y);
	float x, y;
};

class Beizer {
public:
	Beizer (int iteration = 0);
	Point2 Evaluate(float t);
	void DrawCurve(int numberOfPoints = 20);
	void DrawControlPoints();
private:
	vector<Point2> mPoints;
	RGB color;
	double mCircleRadius;
};