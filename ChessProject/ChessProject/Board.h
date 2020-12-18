#pragma once
#include "Piece.h"
#include <iostream>
#include <unordered_set>
#include "Checker.h"
#include <unordered_map>

#define SIZE 8

class Piece;
class Board {

private:
	std::vector<Piece*> sets[2];
	Piece* kings[2];

public:
	Piece* board[SIZE][SIZE];

	Board();
	~Board();
	int move(int color, Checker c1, Checker c2);
	std::string getStringBoard();
	std::unordered_map<Piece*, std::unordered_set<Checker>> getAllPossibleMoves(int color);
	bool isMate(int color);

private:
	int validMove(int color, Checker c1, Checker c2);
	bool isCheck(int color);
	Piece* movePiece(int color, Checker c1, Checker c2);


};
