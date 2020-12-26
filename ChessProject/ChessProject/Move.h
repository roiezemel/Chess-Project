#pragma once
#include "Checker.h"

class Move {

public:
	Move();
	Move(Checker src, Checker dst);
	Move& operator=(Move& other);
	void setSrc(Checker src);
	void setDst(Checker dst);
	void setEval(int eval);
	Checker getSrc() const;
	Checker getDst() const;
	int getEval() const;
	bool operator==(const Move& other) const;

private:
	Checker src;
	Checker dst;
	int eval;

};

namespace std {

	template <>
	struct hash<Move> {
		std::size_t operator()(const Move& k) const {
			using std::size_t;
			using std::hash;
			using std::string;

			return k.getDst().getX() + k.getDst().getY() * SIZE;
		}
	};

}