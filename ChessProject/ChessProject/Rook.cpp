#include "Rook.h"
#define SIZE 8
/*
c'tor of the function
*/
Rook::Rook(Checker che, Board* board, int col, char type):
Runner(che, board, col, type)
{
}
/*
d'tor
*/
Rook::~Rook()
{
}

/*
the function find all the places the rook can go
input: none
output: set with the checkers
*/
std::unordered_set<Move> Rook::getAllPossibleMoves()
{
	return getAllPossibleStraightMoves(_board, _checker);
}

/*
	check if the rook is threatening the other color's king.
*/
bool Rook::isCausingCheck() {
	return isCheckStraight();
}



