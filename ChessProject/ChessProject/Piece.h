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
	void setMoves(int moves);
	int getMoves();

protected:
	Board* _board;
	int _color;
	char _type;
	Checker _checker;
	int moves = 0;
};


namespace std {

	template<>
	struct hash<Piece*> {
		size_t operator()(const Piece* val) const {
			static const size_t shift = (size_t)log2(1 + sizeof(Piece));
			return (size_t)(val) >> shift;
		}
	};

}
