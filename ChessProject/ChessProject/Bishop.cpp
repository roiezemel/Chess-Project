#include "Bishop.h"

/*
c'tor
*/
Bishop::Bishop(Checker che, Board* board, int col, char type):
Piece(che, board, col,type)
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
std::unordered_set<Checker> Bishop::getAllPossibleMoves()
{
	return Bishop::getAllPossibleDiagonalMoves(_board, _checker);
}
/*
the function find all the moves pieces can do on the diagonal
input: the board and the place of the piece
output: set of checkers
*/
std::unordered_set<Checker> Bishop::getAllPossibleDiagonalMoves(Board* _board, Checker _checker)
{
	std::unordered_set<Checker> set;
	int x = _checker.getX();
	int y = _checker.getY();
	int i = 0;
	int j = 0;
	bool flag = true;
	int _color = _board->board[x][y]->getColor();
	for (i = x + 1, j = y + 1; i < SIZE &&  j < SIZE && flag; i++, j++)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	flag = true;
	for (i = x + 1, j = y - 1; i < SIZE && j >= 0 && flag; i++, j--)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	flag = true;
	for (i = x - 1, j = y + 1; i >= 0 && j < SIZE && flag; i--, j++)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	flag = true;
	for (i = x - 1, j = y - 1; i >= 0 && j >= 0 && flag; i--, j--)
	{
		if (!_board->board[i][j])
		{
			set.insert(Checker(i, j));
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			set.insert(Checker(i, j));
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	return set;
}
