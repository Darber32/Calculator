#pragma once
#include "Token.h"

class Number: public Token
{
private:
	double data;
public:
	Number(std::string data);
	double Get_Data();
	void Show();
};

