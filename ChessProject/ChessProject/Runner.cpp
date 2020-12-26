#include "Runner.h"

Runner::Runner(Checker che, Board* board, int col, char type) : Piece(che, board, col, type) {}

Runner::~Runner() {}

/*
the function find all the moves pieces can do on the diagonal
input: the board and the place of the piece
output: set of checkers
*/
std::unordered_set<Move> Runner::getAllPossibleDiagonalMoves(Board* _board, Checker _checker) {
	std::unordered_set<Move> set;
	int x = _checker.getX();
	int y = _checker.getY();
	int i = 0;
	int j = 0;
	bool flag = true;
	int _color = _board->board[x][y]->getColor();
	for (i = x + 1, j = y + 1; i < SIZE && j < SIZE && flag; i++, j++)
	{
		if (!_board->board[i][j])
		{
			this->addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			this->addMoveToSet(Checker(i, j), &set);
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
			this->addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			this->addMoveToSet(Checker(i, j), &set);
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
			this->addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			this->addMoveToSet(Checker(i, j), &set);
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
			this->addMoveToSet(Checker(i, j), &set);
		}
		else if (_board->board[i][j]->getColor() != _color)
		{
			this->addMoveToSet(Checker(i, j), &set);
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	return set;
}

/*
the function find all the straight moves pieces can do
input: pointer to board and the current place of the piece
output: set of checkers
*/
std::unordered_set<Move> Runner::getAllPossibleStraightMoves(Board* _board, Checker _checker)
{
	bool flag = true;
	int i = 0;
	int x = _checker.getX();
	int y = _checker.getY();
	int _color = _board->board[x][y]->getColor();
	std::unordered_set<Move> set;

	for (i = x + 1; i < SIZE && flag; i++)
	{
		if (!_board->board[i][y])
		{
			addMoveToSet(Checker(i, y), &set);
		}
		else if (_board->board[i][y]->getColor() != _color)
		{
			addMoveToSet(Checker(i, y), &set);
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
			addMoveToSet(Checker(i, y), &set);
		}
		else if (_board->board[i][y]->getColor() != _color)
		{
			addMoveToSet(Checker(i, y), &set);
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
			addMoveToSet(Checker(x, i), &set);
		}
		else if (_board->board[x][i]->getColor() != _color)
		{
			addMoveToSet(Checker(x, i), &set);
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
			addMoveToSet(Checker(x, i), &set);
		}
		else if (_board->board[x][i]->getColor() != _color)
		{
			addMoveToSet(Checker(x, i), &set);
			flag = false;
		}
		else
		{
			flag = false;
		}
	}
	return set;
}

bool Runner::isCheckDiagonal() { 
	Checker kingPos = _board->kings[!getColor()]->getPosition();
	int dx = kingPos.getX() - getPosition().getX();
	int dy = kingPos.getY() - getPosition().getY();
	int addi = 0, addj = 0, i = 0, j = 0;

	if (dx != dy || dx != -dy)
		return false;

	addi = dx > 0 ? 1 : -1;
	addj = dy > 0 ? 1 : -1;
	i = getPosition().getX();
	j = getPosition().getY();

	while (i < SIZE && j < SIZE && i >= 0 && j >= 0) {
		if (_board->board[i][j])
			return _board->board[i][j] == _board->kings[!getColor()];

		i += addi;
		j += addj;
	}

	return false;
}

bool Runner::isCheckStraight() {
	Checker kingPos = _board->kings[!getColor()]->getPosition();
	int dx = kingPos.getX() - getPosition().getX();
	int dy = kingPos.getY() - getPosition().getY();
	int addi = 0, addj = 0, i = 0, j = 0;

	if (dx && dy)
		return false;

	addi = dx ? (dx > 0 ? 1 : -1) : 0;
	addj = dy ? (dy > 0 ? 1 : -1) : 0;
	i = getPosition().getX();
	j = getPosition().getY();

	while (i < SIZE && j < SIZE && i >= 0 && j >= 0) {
		if (_board->board[i][j])
			return _board->board[i][j] == _board->kings[!getColor()];

		i += addi;
		j += addj;
	}

	return false;
}
