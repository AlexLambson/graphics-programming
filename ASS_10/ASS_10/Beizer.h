#include <vector>
#include <glut.h>
using namespace std;

double extern screen_x;
double extern screen_y;
enum MenuType{
	MENU_ADD_BEIZER,
	MENU_REMOVE_BEIZER,
	MENU_CHANGE_COLOR
};
enum MenuColor{
	MENU_RED = 35,
	MENU_GREEN,
	MENU_BLUE,
	MENU_BLACK,
	MENU_PURPLE
};
enum SelectType{
	SELECT_BEIZER,
	SELECT_HANDLE
};
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
	void SetColor(MenuColor color);
private:
	vector<Point2> mPoints;
	RGB color;
	double mCircleRadius;
	int activeHandle;
	bool mActive;
	int iteration;
};