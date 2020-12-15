#pragma once
#include "Piece.h"
class Rook: public Piece
{
public:
	Rook(Checker che, Board* board, int col, char type);
	~Rook();
	virtual std::unordered_set <Checker> getAllPossibleMoves();
	static 	std::unordered_set <Checker> getAllPossibleStraightMoves(Board* _board, Checker _checker);
	//virtual bool isValidMove(Checker c1, Checker c2);//maybe not

private:
};


