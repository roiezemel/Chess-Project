#include "Checker.h"
/*
c'tor
*/
Checker::Checker(int i, int j)
{
    x = i;
    y = j;
}

/*
d'tor
*/
Checker::~Checker()
{
}

/*
    Get x.
    Input: none.
    Output: x.
*/
int Checker::getX() const {
    return x;
}

/*
    Get y.
    Input: none.
    Output: y.
*/
int Checker::getY() const {
    return y;
}

/*
    Set x.
    Input: x.
    Output: none.
*/
void Checker::setX(int x) {
    this->x = x;
}

/*
    Set y.
    Input: y.
    Output: none.
*/
void Checker::setY(int y) {
    this->y = y;
}
/*
the operator = of the class
*/
Checker& Checker::operator=( Checker& other)
{
    x = other.getX();
    y = other.getY();
    return *this;
}

/*
    o'tor ==
*/
bool Checker::operator==(const Checker& other) const {
    return x == other.x && y == other.y;
}
