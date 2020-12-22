#include "Rook.h"
#define SIZE 8
/*
c'tor of the function
*/
Rook::Rook(Checker che, Board* board, int col, char type):
Piece(che, board, col, type)
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
std::unordered_set<Checker> Rook::getAllPossibleMoves()
{
	return Rook::getAllPossibleStraightMoves(_board, _checker);
}
/*
the function find all the straight moves pieces can do
input: pointer to board and the current place of the piece
output: set of checkers
*/
std::unordered_set<Checker> Rook::getAllPossibleStraightMoves(Board* _board, Checker _checker)
{
	bool flag = true;
	int i = 0;
	int x = _checker.getX();
	int y = _checker.getY();
	int _color = _board->board[x][y]->getColor();
	std::unordered_set<Checker> set;

	for (i = x + 1; i < SIZE && flag; i++)
	{
		if (!_board->board[i][y])
		{
			set.insert(Checker(i, y));
		}
		else if (_board->board[i][y]->getColor() != _color)
		{
			set.insert(Checker(i, y));
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	flag = true;
	for (i = x - 1; i >= 0 && flag; i--)
	{
		if (!_board->board[i][y])
		{
			set.insert(Checker(i, y));
		}
		else if (_board->board[i][y]->getColor() != _color)
		{
			set.insert(Checker(i, y));
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	flag = true;
	for (i = y + 1; i < SIZE && flag; i++)
	{
		if (!_board->board[x][i])
		{
			set.insert(Checker(x, i));
		}
		else if (_board->board[x][i]->getColor() != _color)
		{
			set.insert(Checker(x, i));
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	flag = true;
	for (i = y - 1; i >= 0 && flag; i--)
	{
		if (!_board->board[x][i])
		{
			set.insert(Checker(x, i));
		}
		else if (_board->board[x][i]->getColor() != _color)
		{
			set.insert(Checker(x, i));
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	return set;
}


