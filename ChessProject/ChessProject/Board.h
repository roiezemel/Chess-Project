#pragma once
#include "Piece.h"
#include <iostream>
#include <unordered_set>
#include "Checker.h"
#include <unordered_map>
#include "Move.h"

#define SIZE 8

class Piece;
class Board {

public:
	Piece* board[SIZE][SIZE];
	const static std::string initalBoard;
	std::unordered_set<Move>* allPossibleMoves[2] = { 0, 0 };
	std::vector<Piece*> sets[2]; // probably deprecated
	Piece* isInCheck[2] = { 0, 0 }; // 0 - false, another pointer - true
	Piece* kings[2]; // pointers of kings of both sides

	
	Board();
	Board(std::string initialBoard);
	Board(Board& board);

	~Board();


	int move(int color, Move move); // done
	std::string getStringBoard(); // done
	bool isMate(int color); // done

	Piece* makeMove(int color, Move move); // done
	
	void updateAllPossibleMoves(int color, bool deletePrev); // done
	
	bool isCheck(int color, Move move); // done
	void makeBackMove(int color, Move move, Piece* eaten); // done
	bool leftAndMadeCheck(Checker src, int kingColor); // done
	void promote(std::string msg, Checker pawn);

private:
	
	int validateMove(int color, Move move); // done
	static Piece* createPiece(char type, int i, int j, Board* board); // done
	int specialMove(int color, Move move); // done
	std::unordered_set<Move>* getAllPossibleMoves(int color); // done

	bool castling = false; // done

};

