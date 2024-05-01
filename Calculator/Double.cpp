#include "Double.h"
#include "Fraction.h"
#include "Matrix.h"
#include "Calculable_Exception.h"

Double::Double(double data)
{
	type = Type::Double;
	this->data = data;
}

void Double::Show()
{
	std::cout << data;
}

double Double::Get_Data()
{
	return data;
}

Data* Double::Plus(Data* b)
{
	if (type == b->Get_Type())
	{
		Double* c = new Double(dynamic_cast<Double*>(b)->data);
		c->data += data;
		return c;
	}
	else if (b->Get_Type() == Type::Fraction)
	{
		Fraction* f = dynamic_cast<Fraction*>(b);
		double x = static_cast<double>(f->numerator) / static_cast<double>(f->denominator);
		Double* c = new Double(data + x);
		return c;
	}
	else if (b->Get_Type() == Type::Matrix)
	{
		int rows = dynamic_cast<Matrix*>(b)->rows, cols = dynamic_cast<Matrix*>(b)->cols;
		std::vector<std::vector<double>> data = dynamic_cast<Matrix*>(b)->data;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				data[i][j] += this->data;
		Matrix * m = new Matrix(rows, cols, &data);
		return m;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Double::Minus(Data* b)
{
	if (type == b->Get_Type())
	{
		Double* c = new Double(dynamic_cast<Double*>(b)->data);
		data -= c->data;
		c->data = data;
		return c;
	}
	else if (b->Get_Type() == Type::Fraction)
	{
		Fraction* f = dynamic_cast<Fraction*>(b);
		double x = static_cast<double>(f->numerator) / static_cast<double>(f->denominator);
		Double* c = new Double(data - x);
		return c;
	}
	else if (b->Get_Type() == Type::Matrix)
	{
		int rows = dynamic_cast<Matrix*>(b)->rows, cols = dynamic_cast<Matrix*>(b)->cols;
		std::vector<std::vector<double>> data = dynamic_cast<Matrix*>(b)->data;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				data[i][j] = this->data - data[i][j];
		Matrix* m = new Matrix(rows, cols, &data);
		return m;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Double::Multiplication(Data* b)
{
	if (type == b->Get_Type())
	{
		Double* c = new Double(dynamic_cast<Double*>(b)->data);
		c->data *= data;
		return c;
	}
	else if (b->Get_Type() == Type::Fraction)
	{
		Fraction* f = dynamic_cast<Fraction*>(b);
		double x = static_cast<double>(f->numerator) / static_cast<double>(f->denominator);
		Double* c = new Double(data * x);
		return c;
	}
	else if (b->Get_Type() == Type::Matrix)
	{
		int rows = dynamic_cast<Matrix*>(b)->rows, cols = dynamic_cast<Matrix*>(b)->cols;
		std::vector<std::vector<double>> data = dynamic_cast<Matrix*>(b)->data;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				data[i][j] *= this->data;
		Matrix* m = new Matrix(rows, cols, &data);
		return m;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Double::Division(Data* b)
{
	if (type == b->Get_Type())
	{
		Double* c = new Double(dynamic_cast<Double*>(b)->data);
		if (c->data == 0)
			throw new Calculable_Exception(Calculable_Exception_Type::Division_By_Zero);
		data /= c->data;
		c->data = data;
		return c;
	}
	else if (b->Get_Type() == Type::Fraction)
	{
		Fraction* f = dynamic_cast<Fraction*>(b);
		double x = static_cast<double>(f->numerator) / static_cast<double>(f->denominator);
		if (x == 0)
			throw new Calculable_Exception(Calculable_Exception_Type::Division_By_Zero);
		Double* c = new Double(data / x);
		return c;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Double::Exponentiation(Data* b)
{
	int indicator = 0;
	Double* data = new Double(this->data);
	if (b->Get_Type() == type)
	{
		indicator = static_cast<int>(dynamic_cast<Double*>(b)->data);
	}
	else if (b->Get_Type() == Type::Fraction)
	{
		Fraction* f = dynamic_cast<Fraction*>(b);
		indicator = static_cast<double>(f->numerator) / static_cast<double>(f->denominator);
	}
	else
		throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
	if (indicator < 0)
	{
		delete data;
		throw new Calculable_Exception(Calculable_Exception_Type::Negative_Indicator);
	}
	else if (indicator == 0)
	{
		data->data = 1;
		return data;
	}
	else
	{
		int c = 1;
		while (c < indicator)
		{
			data->data *= this->data;
			c++;
		}
		return data;
	}
}
