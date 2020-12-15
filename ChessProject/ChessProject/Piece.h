#pragma once
#include "Board.h"
#include <iostream>
#include "Checker.h"
#include <unordered_set>

class Board;
class Piece
{
public:
	Piece(Checker che, Board* board,int col, char type);
	~Piece();
	int getColor();
	//virtual bool isValidMove(Checker c1, Checker c2) = 0;
	virtual char getType();
	virtual std::unordered_set <Checker> getAllPossibleMoves() = 0;
	Checker getPosition();
	void setPosition(Checker c);
protected:
	Board* _board;
	int _color;
	char _type;
	Checker _checker;
};



