#include <vector>
#include <glut.h>
using namespace std;

double extern screen_x;
double extern screen_y;

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
	int MouseHitHandle(int x, int y);
	void ActivateHandle(int i);
	void DeactivateHandle();
	void SetHandlePoint(int handle, int x, int y);
	void ActivateBeizer();
	void DeactivateBeizer();
	bool IsActive();
	void Move(double differenceX, double differenceY);
private:
	vector<Point2> mPoints;
	RGB color;
	double mCircleRadius;
	int activeHandle;
	bool mActive;
};