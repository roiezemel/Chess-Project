#include "Piece.h"

/*
c'tor
*/
Piece::Piece(Checker che, Board* board, int col, char type):
_checker(che.getX(), che.getY())
{
	_board = board;
	_color = col;
	_type = type;
}
/*
d'tor
*/
Piece::~Piece()
{
}
/*
the function gets the color
input: none
output: int
*/
int Piece::getColor()
{
	return _color;
}
/*
the function gets the type
input: none
output: the type
*/
char Piece::getType()
{
	return _type;
}

Checker Piece::getPosition() {
	return _checker;
}

/*
	s'ter
*/
void Piece::setPosition(Checker c) {
	this->_checker = c;
}
