#pragma once
#include "Piece.h"

class Knight :Piece
{
public:
	Knight(Checker che, Board* board, int col, char type);
	~Knight();
	virtual std::unordered_set <Checker> getAllPossibleMoves();
	//virtual bool isValidMove(Checker c1, Checker c2);//maybe not
private:

};