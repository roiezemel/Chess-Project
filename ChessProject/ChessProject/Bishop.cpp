#include "Bishop.h"

/*
c'tor
*/
Bishop::Bishop(Checker che, Board* board, int col, char type):
Runner(che, board, col,type)
{
}
/*
d'tor
*/
Bishop::~Bishop()
{
}
/*
the function find all the places the bishop can go
input: none
output: set with the checkers
*/
std::unordered_set<Move> Bishop::getAllPossibleMoves() {
	return getAllPossibleDiagonalMoves(_board, _checker);
}

/*
	check if the bishop is threatening the other color's king.
*/
bool Bishop::isCausingCheck() {
	return isCheckDiagonal();
}

