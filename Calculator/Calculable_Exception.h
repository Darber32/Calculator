#pragma once
#include "Exception.h"

enum class Calculable_Exception_Type
{
	Division_By_Zero, Type_Mismatch, Matrix_Sum, Matrix_Diff, Matrix_Mult, Matrix_Div, Negative_Indicator
};


class Calculable_Exception: public Exception
{
private:
	Calculable_Exception_Type exception_type;
public:
	Calculable_Exception(Calculable_Exception_Type _type);
	Calculable_Exception_Type Get_Exception_Type();
};

