#pragma once
#include "Piece.h"

class Bishop: public Piece
{
public:
	Bishop(Checker che, Board* board, int col, char type);
	~Bishop();
	virtual std::unordered_set <Checker> getAllPossibleMoves();
	//virtual bool isValidMove(Checker c1, Checker c2);//maybe not
	static std::unordered_set <Checker> getAllPossibleDiagonalMoves(Board* _board, Checker _checker);

};



