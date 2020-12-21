#pragma once
#include "Board.h"

typedef struct move {
	move();
	move& operator=(move& other);
	Checker src;
	Checker dst;
	int eval;
}move;
class MiniMax
{
public:
	MiniMax(Board* board);
	~MiniMax();
	int eval(Board* board) const;
	int minMax(int depth, Board* board, int color);
	std::unordered_set<move> getAllMoves(Board* board, int color);
	Board* copyBoard(Board* board);
private:
	Board* board;
	move selectedMove;

};



