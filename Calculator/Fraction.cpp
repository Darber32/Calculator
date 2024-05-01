#include "Fraction.h"
#include "Calculable_Exception.h"

void Fraction::Shorten_The_Fraction()
{
	int a = abs(numerator), b = abs(denominator);
	while (a * b != 0)
	{
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	int nod = a + b;
	numerator /= nod;
	denominator /= nod;
}

Fraction::Fraction(int _numerator, int _denominator) : numerator(_numerator), denominator(_denominator)
{
	type = Type::Fraction;
	if (denominator == 0)
		throw new Calculable_Exception(Calculable_Exception_Type::Division_By_Zero);
	if (denominator < 0)
	{
		numerator *= -1;
		denominator *= -1;
	}
}

void Fraction::Show()
{
	Shorten_The_Fraction();
	if (abs(numerator) < abs(denominator))
		std::cout << numerator << "|" << denominator;
	else
	{
		if (numerator == denominator)
			std::cout << 1;
		else
		{
			if (numerator % denominator == 0)
				std::cout << numerator / denominator;
			else
				std::cout << numerator / denominator << "[" << abs(numerator % denominator) << "|" << abs(denominator) << "]";
		}
	}
}

Data* Fraction::Plus(Data* b)
{
	if (b->Get_Type() == type)
	{
		Fraction* f = new Fraction(dynamic_cast<Fraction*>(b)->numerator, dynamic_cast<Fraction*>(b)->denominator);
		if (denominator != f->denominator)
		{
			int temp = denominator;
			numerator *= f->denominator;
			denominator *= f->denominator;
			f->numerator *= temp;
			f->denominator *= temp;
		}
		f->numerator += numerator;
		return f;
	}
	else if (b->Get_Type() == Type::Double)
	{
		double c = dynamic_cast<Double*>(b)->Get_Data();
		double d = static_cast<double>(numerator) / static_cast<double>(denominator);
		Double* data = new Double(c + d);
		return data;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Fraction::Minus(Data* b)
{
	if (b->Get_Type() == type)
	{
		Fraction* f = new Fraction(dynamic_cast<Fraction*>(b)->numerator, dynamic_cast<Fraction*>(b)->denominator);
		if (denominator != f->denominator)
		{
			int temp = denominator;
			numerator *= f->denominator;
			denominator *= f->denominator;
			f->numerator *= temp;
			f->denominator *= temp;
		}
		numerator -= f->numerator;
		f->numerator = numerator;
		return f;
	}
	else if (b->Get_Type() == Type::Double)
	{
		double c = dynamic_cast<Double*>(b)->Get_Data();
		double d = static_cast<double>(numerator) / static_cast<double>(denominator);
		Double* data = new Double(d - c);
		return data;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Fraction::Multiplication(Data* b)
{
	if (b->Get_Type() == type)
	{
		Fraction* f = new Fraction(dynamic_cast<Fraction*>(b)->numerator, dynamic_cast<Fraction*>(b)->denominator);
		f->numerator *= numerator;
		f->denominator *= denominator;
		return f;
	}
	else if (b->Get_Type() == Type::Double)
	{
		double c = dynamic_cast<Double*>(b)->Get_Data();
		double d = static_cast<double>(numerator) / static_cast<double>(denominator);
		Double* data = new Double(d * c);
		return data;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Fraction::Division(Data* b)
{
	if (b->Get_Type() == type)
	{
		Fraction* f = new Fraction(dynamic_cast<Fraction*>(b)->numerator, dynamic_cast<Fraction*>(b)->denominator);
		if (f->numerator == 0)
			throw new Calculable_Exception(Calculable_Exception_Type::Division_By_Zero);
		numerator *= f->denominator;
		denominator *= f->numerator;
		f->numerator = numerator;
		f->denominator = denominator;
		return f;
	}
	else if (b->Get_Type() == Type::Double)
	{
		double c = dynamic_cast<Double*>(b)->Get_Data();
		if (c == 0)
			throw new Calculable_Exception(Calculable_Exception_Type::Division_By_Zero);
		double d = static_cast<double>(numerator) / static_cast<double>(denominator);
		Double* data = new Double(d / c);
		return data;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Fraction::Exponentiation(Data* b)
{
	int indicator = 0;
	if (b->Get_Type() == Type::Double)
	{
		indicator = static_cast<int>(dynamic_cast<Double*>(b)->Get_Data());
	}
	else if (b->Get_Type() == type)
	{
		Fraction* f = dynamic_cast<Fraction*>(b);
		indicator = static_cast<double>(f->numerator) / static_cast<double>(f->denominator);
	}
	else
		throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
	if (indicator < 0)
		throw new Calculable_Exception(Calculable_Exception_Type::Negative_Indicator);
	else if (indicator == 0)
	{
		return new Double(1);
	}
	else
	{
		Fraction* f = new Fraction(numerator, denominator);
		int c = 1;
		while (c < indicator)
		{
			f->numerator *= numerator;
			f->denominator *= denominator;
			c++;
		}
		return f;
	}
}
