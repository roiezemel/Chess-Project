#pragma once
#include <iostream>

#define SIZE 8

class Checker
{

private:
	int x;
	int y;
public:
	Checker(int i, int j);
	~Checker();
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);
	Checker& operator=( Checker& other);
	bool operator==(const Checker& other) const;

};

namespace std {

	template <>
	struct hash<Checker> {
		std::size_t operator()(const Checker& k) const {
			using std::size_t;
			using std::hash;
			using std::string;

			return k.getX() + k.getY() * SIZE;
		}
	};

}
