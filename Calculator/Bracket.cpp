#include "Bracket.h"

Bracket::Bracket(char c)
{
	type = Token_Type::Bracket;
	type_of_bracket = c;
}

char Bracket::Get_Bracket_Type()
{
	return type_of_bracket;
}

void Bracket::Show()
{
	std::cout << type_of_bracket;
}
