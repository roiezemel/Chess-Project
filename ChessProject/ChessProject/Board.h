#pragma once
#include "Piece.h"
#include <iostream>
#include <unordered_set>
#include "Checker.h"
#include <unordered_map>

#define SIZE 8

class Piece;
class Board {

public:
	Piece* board[SIZE][SIZE];
	const static std::string initalBoard;
	
	Board();
	Board(std::string initialBoard);
	~Board();
	int move(int color, Checker c1, Checker c2);
	std::string getStringBoard();
	std::unordered_map<Piece*, std::unordered_set<Checker>>* getAllPossibleMoves(int color);
	bool isMate(int color);
	bool isCastling();
	Piece* movePiece(int color, Checker c1, Checker c2);
	std::vector<Piece*> sets[2];
private:
	
	Piece* kings[2];
	std::unordered_map <Piece*, std::unordered_set<Checker>>* allPossibleMoves[2] = {0, 0};
	int validMove(int color, Checker c1, Checker c2);
	bool isCheck(int color);
	void updateAllPossibleMoves(int color);
	static Piece* createPiece(char type, int i, int j, Board* board);
	int isCheckBothSides(int color);
	int specialMove(int color, Checker c1, Checker c2);
	bool castling = false;

};

