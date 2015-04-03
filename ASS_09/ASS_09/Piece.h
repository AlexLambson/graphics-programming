#include <stdlib.h>
#include <vector>
using namespace std;
#include "graphics.h"

enum PieceType{
	ROOK,
	PAWN,
	KING,
	QUEEN,
	BISHOP,
	KNIGHT
};
enum PieceColor{
	RED,
	BLUE,
	GREEN,
	WHITE,
	BRIGHT_GREEN,
	BLACK,
	GRAY,
	CREAM
};
struct Position{
	int x, y, z;
};

class Piece
{
public:
	Piece();
	Piece(int x, int y, int z, char filename[], PieceColor color);
	void Draw();
	void setPosition(int x, int y, int z);
	void setRotation(int x, int y, int z);
	Position getRotation();
	Position getPosition();
	GLfloat * getColor();
private:
	char* mPieceType;
	Position mPosition;
	PieceColor mColor;
	bool isNull;
	Position rotation;
};

class Board{
public:
	Board();
	void Draw();
};