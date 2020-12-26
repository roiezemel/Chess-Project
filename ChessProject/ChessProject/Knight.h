#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(Checker che, Board* board, int col, char type);
	~Knight();
	virtual std::unordered_set <Move> getAllPossibleMoves();
	virtual bool isCausingCheck();
	//virtual bool isValidMove(Checker c1, Checker c2);//maybe not
private:

};