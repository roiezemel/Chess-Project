#pragma once
#include "Piece.h"
#include <iostream>
#include <unordered_set>
#include "Checker.h"
#include <unordered_map>

#define BOARD_SIZE

class Piece;
class Board {

private:
	std::vector<Piece*> whites;
	std::vector<Piece*> blacks;
	Piece* blackKing;
	Piece* whiteKing;

public:
	Piece*** board;

	Board();
	~Board();
	void move(int color, Checker c1, Checker c2);
	bool isCheck(int color);
	std::string getStringBoard();
	std::unordered_map<Piece*, std::unordered_set<Checker>> getAllPossibleMoves(int color);


};

/*

#include <boost/functional/hash.hpp>

namespace std {
  template <>
  struct hash<Checker>
  {
	typedef Checker      argument_type;
	typedef std::size_t  result_type;

	result_type operator()(const Checker & t) const
	{
	  std::size_t val { 0 };
	  boost::hash_combine(val,t.x);
	  boost::hash_combine(val,t.y);
	  return val;
	}
  };
}
*/
