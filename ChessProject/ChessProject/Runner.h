#pragma once
#include "Piece.h"
#include "Board.h"
#include "Checker.h"

class Runner : public Piece {

public:
	Runner(Checker che, Board* board, int col, char type);
	~Runner();
	std::unordered_set <Move> getAllPossibleDiagonalMoves(Board* _board, Checker _checker);
	std::unordered_set<Move> getAllPossibleStraightMoves(Board* _board, Checker _checker);
	bool isCheckDiagonal();
	bool isCheckStraight();


};

