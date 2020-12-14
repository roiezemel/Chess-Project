#pragma once
#define SIZE 8
class Piece;
class Board
{
public:
	Board();
	~Board();

	Piece* board [SIZE][SIZE];
private:
};

Board::Board()
{
}

Board::~Board()
{
}

