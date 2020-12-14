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
copy c'tor
*/
Checker::Checker(Checker& che)
{
    x = che.getX();
    y = che.setY();
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
int Checker::getX() {
    return x;
}

/*
    Get y.
    Input: none.
    Output: y.
*/
int Checker::getY() {
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
