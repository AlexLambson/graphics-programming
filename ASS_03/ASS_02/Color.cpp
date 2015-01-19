#include "Color.h"
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

Color::Color(){
	this->setColors(0.0, 0.0, 0.0);
}
Color::Color(const double red, const double green, const double blue){
	this->setColors(red, green, blue);
}
vector<double> Color::GetColors(){
	vector<double> colors(3);
	colors[0] = this->r;
	colors[1] = this->g;
	colors[2] = this->b;
	return colors;
}
void Color::setRed(const double red){
	this->r = red;
}
void Color::setGreen(const double green){
	this->g = green;
}
void Color::setBlue(const double blue){
	this->b = blue;
}
void Color::setColors(const double red, const double green, const double blue){
	this->setRed(red);
	this->setGreen(green);
	this->setBlue(blue);
}
string Color::Print(){
	return	"Red: " + to_string(this->r) + "\n" + 
			"Green: " + to_string(this->g) + "\n" + 
			"Blue: " + to_string(this->b) + "\n";
}
std::ostream& operator<< (std::ostream &os, Color &inColor){
	os << inColor.Print();
	return os;
}
