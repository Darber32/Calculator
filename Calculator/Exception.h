#pragma once
enum class Exception_Type
{
	Formula_Exception, Calculable_Exception 
};

class Exception
{
protected:
	Exception_Type type;
public:
	Exception_Type Get_Type();
};

