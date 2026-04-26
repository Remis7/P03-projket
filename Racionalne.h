#pragma once

#include <iostream>
#include <stdexcept>
#include <numeric>
#include <cmath>

using namespace std;

class Racionalne
{
private:
	int citatel;
	int menovatel;

	void zjednodus();

public:
	// konstruktor
	Racionalne(int c = 0, int m = 1);
	// getery
	int getNum() const;
	int getDen() const;

	// binarne operatory
	friend Racionalne operator+(const Racionalne& lhs, const Racionalne& rhs);
	friend Racionalne operator-(const Racionalne& lhs, const Racionalne& rhs);
	friend Racionalne operator*(const Racionalne& lhs, const Racionalne& rhs);
	friend Racionalne operator/(const Racionalne& lhs, const Racionalne& rhs);

	// operatory porovnavania
	bool operator==(const Racionalne& other) const;
	bool operator!=(const Racionalne& other) const;

	// operator na vypis
	friend ostream& operator<<(std::ostream& os, const Racionalne& r);
};
