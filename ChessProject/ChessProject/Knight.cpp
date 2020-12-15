#include "Knight.h"


/*
c'tor
*/
Knight::Knight(Checker che, Board* board, int col, char type) :
	Piece(che, board, col, type)
{
}
/*
d'tor
*/
Knight::~Knight()
{
}
/*
the function find all the posible moves of the knight
input: none
output: set of checkers
*/
std::unordered_set<Checker> Knight::getAllPossibleMoves()
{
	std::unordered_set<Checker> set;
	int x = _checker.getX();
	int y = _checker.getY();
	int i = x + 2;
	int j = y + 1;
	if (i < SIZE && j < SIZE)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
		}
	}
	i = x + 2;
	j = y - 1;
	if (i < SIZE && j >= 0)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
		}
	}
	i = x + 1;
	j = y + 2;
	if (i < SIZE && j < SIZE)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
		}
	}
	i = x + 1;
	j = y - 2;
	if (i < SIZE && j >= 0)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
		}
	}
	i = x - 1;
	j = y + 2;
	if (i >= 0 && j < SIZE)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
		}
	}
	i = x - 1;
	j = y - 2;
	if (i >= 0 && j >= 0)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
		}
	}
	i = x - 2;
	j = y + 1;
	if (i >= 0 && j < SIZE)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
		}
	}
	i = x - 2;
	j = y - 1;
	if (i >= 0 && j >= 0)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
		}
	}
	return set;
}
