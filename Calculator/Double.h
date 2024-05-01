#pragma once
#include "Data.h"

class Double : public Data
{
private:
	double data;
public:
	Double(double data);
	void Show();
	double Get_Data();
	Data* Plus(Data* b);
	Data* Minus(Data* b);
	Data* Multiplication(Data* b);
	Data* Division(Data* b);
	Data* Exponentiation(Data * b);
};

