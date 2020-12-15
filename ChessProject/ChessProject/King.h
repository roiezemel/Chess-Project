#pragma once
#include "Piece.h"
class King:public Piece
{
public:
	King(Checker che, Board* board, int col, char type);
	~King();
	virtual std::unordered_set <Checker> getAllPossibleMoves();
	//virtual bool isValidMove(Checker c1, Checker c2);//maybe not

private:

};


