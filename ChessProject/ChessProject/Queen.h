#pragma once
#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"
class Queen: public Runner
{
public:
	Queen(Checker che, Board* board, int col, char type);
	~Queen();
	virtual std::unordered_set <Move> getAllPossibleMoves();
	virtual bool isCausingCheck();
	//virtual bool isValidMove(Checker c1, Checker c2);//maybe not
private:

};


