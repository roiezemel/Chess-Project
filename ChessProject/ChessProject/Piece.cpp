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

/*
	Set moves.
	Input: moves.
	Output: none.
*/
void Piece::setMoves(int moves) {
	this->moves = moves;
}

/*
	Get moves.
	Input: none.
	Output: moves.
*/
int Piece::getMoves() {
	return moves;
}

void Piece::addMoveToSet(Checker c, std::unordered_set<Move>* set) {
	if (_board->kings[!getColor()]->getPosition() == c)
		_board->isInCheck[!getColor()] = this;

	Move move(getPosition(), c);
	set->insert(move);
}
