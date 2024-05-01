#pragma once
#include "Data.h"
#include "Double.h"

class Fraction : public Data
{
	friend Double;
private:
	int numerator, denominator;
	void Shorten_The_Fraction();
public:
	Fraction(int _numerator, int _denominator);
	void Show();
	Data* Plus(Data* b);
	Data* Minus(Data* b);
	Data* Multiplication(Data* b);
	Data* Division(Data* b);
	Data* Exponentiation(Data* b);
};

