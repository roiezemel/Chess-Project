#pragma once
#include "Piece.h"
#include "Runner.h"
class Rook: public Runner
{
public:
	Rook(Checker che, Board* board, int col, char type);
	~Rook();
	virtual std::unordered_set <Move> getAllPossibleMoves();
	virtual bool isCausingCheck();
	//virtual bool isValidMove(Checker c1, Checker c2);//maybe not

private:
};


