#include "Queen.h"
/*
c'tor 
*/
Queen::Queen(Checker che, Board* board, int col, char type) :
Piece(che, board, col, type)
{
}
/*
d'tor
*/
Queen::~Queen()
{
}
/*
the function find all the places the queen can go
input: none
output: set off checkers
*/
std::unordered_set<Checker> Queen::getAllPossibleMoves()
{
	std::unordered_set<Checker> set1 = Bishop::getAllPossibleDiagonalMoves(_board, _checker);
	std::unordered_set<Checker> set2 = Rook::getAllPossibleStraightMoves(_board, _checker);
	for (Checker checker: set1)
	{

	}
}
