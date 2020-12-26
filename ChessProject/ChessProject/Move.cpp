#include "Move.h"

Move::Move() : src(0, 0), dst(0, 0), eval(0) {}

Move::Move(Checker src, Checker dst) : src(src), dst(dst), eval(0) {}

Move& Move::operator=(Move& other) {
	this->src = other.src;
	this->dst = other.dst;
	this->eval = other.eval;
	return *this;
}

void Move::setSrc(Checker src) {
	this->src = src;
}

void Move::setDst(Checker dst) {
	this->dst = dst;
}

void Move::setEval(int eval) {
	this->eval = eval;
}

Checker Move::getSrc() const {
	return src;
}

Checker Move::getDst() const {
	return dst;
}

int Move::getEval() const {
	return eval;
}

bool Move::operator==(const Move& other) const {
	return src == other.src && dst == other.dst;
}

