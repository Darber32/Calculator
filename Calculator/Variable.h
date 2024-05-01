#pragma once
#include "Token.h"
#include "Data.h"
class Variable : public Token
{
private:
	std::string name;
	Data* data;
public:
	Variable(std::string name, Data* data);
	Data* Get_Data();
	void Show();
};

