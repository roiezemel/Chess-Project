#include "Queen.h"
/*
c'tor
*/
Queen::Queen(Checker che, Board* board, int col, char type) :
	Runner(che, board, col, type)
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
std::unordered_set<Move> Queen::getAllPossibleMoves()
{
	std::unordered_set<Move> set1 = getAllPossibleDiagonalMoves(_board, _checker);
	std::unordered_set<Move> set2 = getAllPossibleStraightMoves(_board, _checker);
	for (const Move& move : set1)
	{
		set2.insert(move);
	}
	return set2;
}

/*
	check if the queen is threatening the other color's king.
*/
bool Queen::isCausingCheck() {
	return isCheckDiagonal() || isCheckStraight();
}
