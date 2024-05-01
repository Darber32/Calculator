#include "Operation.h"

Operation::Operation(char c)
{
	type = Token_Type::Operation;
	type_of_operation = c;
	if (c == '^')
		priority = 3;
	else if (c == '*' or c == '/')
		priority = 2;
	else
		priority = 1;
}


char Operation::Get_Operation_Type()
{
	return type_of_operation;
}

int Operation::Get_Priority()
{
	return priority;
}

void Operation::Show()
{
	std::cout << type_of_operation;
}
