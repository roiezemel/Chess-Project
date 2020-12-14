#pragma once
#include "Piece.h"
#include "Checker.h"
#include "Board.h"

class Pawn : public Piece {
	
public:
	Pawn(Checker che, Board* board, int col, char type);
	~Pawn();
	virtual std::unordered_set <Checker> getAllPossibleMoves();

};

