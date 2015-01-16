#ifndef _COLOR_CLASS_H_
#define _COLOR_CLASS_H_

#include <cstdlib>
#include <vector>
#include <string>

class Color{
public:
	Color();
	Color(const double red, const double green, const double blue);
	
	std::vector<double> GetColors();
	std::string Print();
	
	void setRed(double red);
	void setGreen(double green);
	void setBlue(double blue);
	void setColors(const double red, const double green, const double blue);

protected:
	double r, g, b;
};
std::ostream& operator<< (std::ostream& stream, const Color& inColor);

#endif