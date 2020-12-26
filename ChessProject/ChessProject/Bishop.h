#pragma once
#include "Piece.h"
#include "Runner.h"

class Bishop: public Runner
{
public:
	Bishop(Checker che, Board* board, int col, char type);
	~Bishop();
	virtual std::unordered_set <Move> getAllPossibleMoves();
	virtual bool isCausingCheck();
	//virtual bool isValidMove(Checker c1, Checker c2);//maybe not

};



