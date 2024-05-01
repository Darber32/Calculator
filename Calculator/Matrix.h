#pragma once
#include <vector>
#include "Data.h"
#include "Double.h"
#include "Fraction.h"

class Matrix : public Data
{
	friend Double;
private:
	int rows, cols;
	std::vector<std::vector<double>> data;
public:
	Matrix(int rows, int cols, std::vector<std::vector<double>>* data);
	void Show();
	Data* Plus(Data* b);
	Data* Minus(Data* b);
	Data* Multiplication(Data* b);
	Data* Division(Data* b);
	Data* Exponentiation(Data* b);
};

