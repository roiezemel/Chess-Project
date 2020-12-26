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
std::unordered_set<Move> Knight::getAllPossibleMoves()
{
	std::unordered_set<Move> set;
	int x = _checker.getX();
	int y = _checker.getY();
	int i = x + 2;
	int j = y + 1;
	if (i < SIZE && j < SIZE)
	{
		if (!_board->board[i][j])
		{
			addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			addMoveToSet(Checker(i, j), &set);
		}
	}
	i = x + 2;
	j = y - 1;
	if (i < SIZE && j >= 0)
	{
		if (!_board->board[i][j])
		{
			addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			addMoveToSet(Checker(i, j), &set);
		}
	}
	i = x + 1;
	j = y + 2;
	if (i < SIZE && j < SIZE)
	{
		if (!_board->board[i][j])
		{
			addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			addMoveToSet(Checker(i, j), &set);
		}
	}
	i = x + 1;
	j = y - 2;
	if (i < SIZE && j >= 0)
	{
		if (!_board->board[i][j])
		{
			addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			addMoveToSet(Checker(i, j), &set);
		}
	}
	i = x - 1;
	j = y + 2;
	if (i >= 0 && j < SIZE)
	{
		if (!_board->board[i][j])
		{
			addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			addMoveToSet(Checker(i, j), &set);
		}
	}
	i = x - 1;
	j = y - 2;
	if (i >= 0 && j >= 0)
	{
		if (!_board->board[i][j])
		{
			addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			addMoveToSet(Checker(i, j), &set);
		}
	}
	i = x - 2;
	j = y + 1;
	if (i >= 0 && j < SIZE)
	{
		if (!_board->board[i][j])
		{
			addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			addMoveToSet(Checker(i, j), &set);
		}
	}
	i = x - 2;
	j = y - 1;
	if (i >= 0 && j >= 0)
	{
		if (!_board->board[i][j])
		{
			addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			addMoveToSet(Checker(i, j), &set);
		}
	}
	return set;
}

/*
	check if the knight is threatening the other color's king.
*/
bool Knight::isCausingCheck() {
	Checker kingPos = _board->kings[!getColor()]->getPosition();
	int dx = kingPos.getX() - getPosition().getX();
	int dy = kingPos.getY() - getPosition().getY();

	dx = dx < 0 ? -dx : dx;
	dy = dy < 0 ? -dy : dy; // absolute values

	return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}
