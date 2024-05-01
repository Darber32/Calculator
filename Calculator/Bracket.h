#pragma once
#include "Token.h"
class Bracket : public Token
{
private:
	char type_of_bracket;
public:
	Bracket(char c);
	char Get_Bracket_Type();
	void Show();
};

