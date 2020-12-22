#pragma once
#include "Board.h"

typedef struct move {
	move();
	move(Checker src, Checker dst);
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
	move getBestMove(int depth, int color);

private:
	Board* board;
	move selectedMove;

	static int placeKing[SIZE][SIZE];
	static int placeQueen[SIZE][SIZE];
	static int placeKnight[SIZE][SIZE];
	static int placeRook[SIZE][SIZE];
	static int placeBishop[SIZE][SIZE];
	static int placePawn[SIZE][SIZE];
	static int value;
	static int king;
	static int queen;
	static int rook;		
	static int bishop;
	static int knight;
	static int pawn;

	int minMax(int depth, Board* board, bool isPlayerColor, int color);
	int eval(Board* board, int color) const;
	std::vector<move> getAllMoves(Board* board, int color);

};



