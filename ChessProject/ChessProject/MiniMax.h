#pragma once
#include "Board.h"

class MiniMax
{
public:
	MiniMax(Board* board);
	~MiniMax();
	Move getBestMove( int color, int (*determineDepth)(int, int));

private:
	Board* board;
	Move selectedMove;
	Move lastMove;

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
	static int allMovesCount;
	static int skipped;
	static int recursion;

	int minMax(int depth, Board* board, bool isPlayerColor, int color, int alpha, int beta);
	int eval(Board* board, int color) const;
	std::vector<Move> getAllMoves(Board* board, int currentColor);

};



