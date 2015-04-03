#pragma once

//keep track of a cell's position in an array
struct ArrayPosition{
	int posX, posY;
};
struct WorldPosition{
	double x, y, z;
	double red, green, blue, alpha;
};
struct WorldSize{
	int x, y;
};
//only use in glcolor3ub();
/*struct Color{
	unsigned char r, g, b;
};*/
namespace Key{
	enum Type{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
}
enum currentView{
	perspective_view,
	top_view,
	rat_view
};
extern double waterHeight;