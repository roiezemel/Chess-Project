#pragma once
class Checker
{

private:
	int x;
	int y;
public:
	Checker(int i, int j);
	Checker(Checker& che);
	~Checker();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	Checker& operator=( Checker& other);
};
