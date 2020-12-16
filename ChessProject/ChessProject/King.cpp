#include "King.h"

/*
c'tor of the class
*/
King::King(Checker che, Board* board, int col, char type):
Piece(che, board, col, type)
{
}
/*
d'tor of the class
*/
King::~King()
{
}
/*
the function find all the places the king can go
input: none
output: set with the checkers
*/
std::unordered_set<Checker> King::getAllPossibleMoves()
{
	std::unordered_set<Checker> set;
	int x = _checker.getX();
	int y = _checker.getY();
	int i = 0;
	int j = 0;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if (i >= 0 && i < SIZE && j >= 0 && j < SIZE) {
				if (!_board->board[i][j])
				{
					set.insert(Checker(i, j));
				}
				else if (_board->board[i][j]->getColor() != getColor())
				{
					set.insert(Checker(i, j));
				}
			}
		}
	}

	return set;
}
