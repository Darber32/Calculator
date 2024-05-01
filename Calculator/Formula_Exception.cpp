#include "Formula_Exception.h"

Formula_Exception::Formula_Exception(Formula_Exception_Type _type): exception_type(_type)
{
	type = Exception_Type::Formula_Exception;
}

Formula_Exception_Type Formula_Exception::Get_Exception_Type()
{
	return exception_type;
}
