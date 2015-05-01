#include <stdlib.h>
#include <vector>
using namespace std;
#include "graphics.h"

enum PieceType{
	ROOK = 100,
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
struct Scale{
	double x, y, z;
};
class Piece
{
public:
	Piece();
	Piece(int x, int y, int z, unsigned int pieceType, PieceColor color, GLuint id);
	void Draw();
	void setPosition(int x, int y, int z);
	void setRotation(int x, int y, int z);
	Position getRotation();
	Position getPosition();
	Scale getScale();
	void setScale(Scale scale);
	GLfloat * getColor();
	GLuint glId;
	unsigned int mPieceType;
private:
	void initGL();
	Position mPosition;
	PieceColor mColor;
	bool isNull;
	Position rotation;
	Scale mScale;
};

class Board{
public:
	Board();
	void Draw();
};