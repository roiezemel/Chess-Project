#include "Move.h"

/*
c'tor
*/
Move::Move() : src(0, 0), dst(0, 0), eval(0) {}

/*
c'tor 
*/
Move::Move(Checker src, Checker dst) : src(src), dst(dst), eval(0) {}

/*
op'tor
*/
Move& Move::operator=(Move& other) {
	this->src = other.src;
	this->dst = other.dst;
	this->eval = other.eval;
	return *this;
}

/*
	get src
*/
void Move::setSrc(Checker src) {
	this->src = src;
}

/*
	get dst
*/
void Move::setDst(Checker dst) {
	this->dst = dst;
}

/*
	set eval
*/
void Move::setEval(int eval) {
	this->eval = eval;
}

/*
	get src
*/
Checker Move::getSrc() const {
	return src;
}

/*
	get dst
*/
Checker Move::getDst() const {
	return dst;
}

/*
	get eval
*/
int Move::getEval() const {
	return eval;
}

/*
op'tor
*/
bool Move::operator==(const Move& other) const {
	return src == other.src && dst == other.dst;
}

