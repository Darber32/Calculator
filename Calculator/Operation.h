#pragma once
#include "Token.h"
class Operation : public Token
{
private:
	char type_of_operation;
	int priority;
public:
	Operation(char c);
	char Get_Operation_Type();
	int Get_Priority();
	void Show();
};

