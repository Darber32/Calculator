#include "Calculable_Exception.h"

Calculable_Exception::Calculable_Exception(Calculable_Exception_Type _type) : exception_type(_type)
{
	type = Exception_Type::Calculable_Exception;
}

Calculable_Exception_Type Calculable_Exception::Get_Exception_Type()
{
	return exception_type;
}
