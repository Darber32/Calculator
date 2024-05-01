#pragma once
#include <iostream>
#include <string>
enum class Token_Type
{
	Number, Variable, Operation, Bracket
};

class Token
{
protected:
	Token_Type type;
public:
	Token_Type Get_Type();
	virtual void Show() = 0;
};

