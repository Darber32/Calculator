#pragma once
#include <iostream>

#include "Number.h"
enum class Type
{
	Double, Fraction, Matrix 
};

class Data
{
protected:
	Type type;
public:
	Type Get_Type();
	virtual void Show() = 0;
	virtual Data* Plus(Data* b) = 0;
	virtual Data* Minus(Data* b) = 0;
	virtual Data* Multiplication(Data* b) = 0;
	virtual Data* Division(Data* b) = 0;
	virtual Data* Exponentiation(Data * b) = 0;
};