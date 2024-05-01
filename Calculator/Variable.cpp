#include "Variable.h"

Variable::Variable(std::string name, Data* data)
{
	type = Token_Type::Variable;
	this->name = name;
	this->data = data;
}


Data* Variable::Get_Data()
{
	return data;
}

void Variable::Show()
{
	std::cout << name;
}
