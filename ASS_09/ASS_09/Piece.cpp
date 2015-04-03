#include "Piece.h"

Piece::Piece(){
	this->setPosition(0, 0, 0);
	this->isNull = true;
}
Piece::Piece(int x, int y, int z, char filename[], PieceColor color){
	this->setPosition(x, y, z);
	this->mPieceType = filename;
	this->mColor = color;
	this->isNull = false;
	this->setRotation(0, 0, 0);
}
void Piece::setPosition(int x, int y, int z){
	this->mPosition.x = x;
	this->mPosition.y = y;
	this->mPosition.z = z;
}
void Piece::setRotation(int x, int y, int z){
	// x will tip up or down the board
	// y will spin a piece
	// z will tip left and right
	this->rotation.x = x;
	this->rotation.y = y;
	this->rotation.z = z;
}
Position Piece::getRotation(){
	return this->rotation;
}
Position Piece::getPosition(){
	return this->mPosition;
}
void Piece::Draw(){
	if (this->isNull){
		return;
	}
	if (this->mPosition.y <= -30000){
		this->isNull = true;
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->getColor());
	//rotate
	//move
	glPushMatrix();
	glTranslatef(this->mPosition.x, this->mPosition.y, this->mPosition.z);
	glRotated(this->rotation.x, 1, 0, 0);
	glRotated(this->rotation.y, 0, 1, 0);
	glRotated(this->rotation.z, 0, 0, 1);
	DrawPiece(this->mPieceType);
	glPopMatrix();
}
GLfloat* Piece::getColor(){
	GLfloat* color;
	switch (this->mColor)
	{
	case RED:
		color = redMaterial;
		break;
	case WHITE:
		color = whiteMaterial;
		break;
	case BLUE:
		color = blueMaterial;
		break;
	case BLACK:
		color = blackMaterial;
		break;
	case GREEN:
		color = greenMaterial;
		break;
	case GRAY:
		color = grayMaterial;
		break;
	case BRIGHT_GREEN:
		color = brightGreenMaterial;
		break;
	case CREAM:
		color = creamMaterial;
		break;
	default:
		color = blackMaterial;
		break;
	}
	return color;
}
Board::Board(){
	//nothing
}
void Board::Draw(){
	for (int x = 0; x < 8; x++){
		for (int y = 0; y < 8; y++){
			GLfloat* color;
			if ((x + y) % 2 == 0){
				color = blackMaterial;
			}
			else {
				color = whiteMaterial;
			}
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			glBegin(GL_QUADS);
			glNormal3d(0,1,0);
			glVertex3i(x * CELL_SIZE +500, BOARD_HEIGHT, y * CELL_SIZE+500);
			glVertex3i((x + 1) * CELL_SIZE+500, BOARD_HEIGHT, y * CELL_SIZE+500);
			glVertex3i((x+1) * CELL_SIZE+500, BOARD_HEIGHT, (y + 1) * CELL_SIZE+500);
			glVertex3i(x * CELL_SIZE + 500, BOARD_HEIGHT, (y + 1) * CELL_SIZE + 500);
			glEnd();
		}
	}
	glBegin(GL_QUADS);
	{	
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brownMaterial);
		glNormal3d(1, 0, 0);
		glVertex3i(500, -CELL_SIZE, 500);
		glVertex3i(500, -CELL_SIZE, CELL_SIZE * 8 + 500);
		glVertex3i(500, BOARD_HEIGHT, CELL_SIZE * 8 + 500);
		glVertex3i(500, BOARD_HEIGHT, 500);
	}
	glEnd();
}