#pragma once
#include "Exception.h"

enum class Formula_Exception_Type
{
	Bracket_Mismatch, Lack_Of_Operands, No_Operation, Unexpected_Symbol, Wrong_File
};

class Formula_Exception : public Exception
{
private:
	Formula_Exception_Type exception_type;
public:
	Formula_Exception(Formula_Exception_Type _type);
	Formula_Exception_Type Get_Exception_Type();
};

