#include "Number.h"

Number::Number(std::string data)
{
	type = Token_Type::Number;
	int index = 0;
	if (data[0] != '.')
	{
		this->data = std::stoi(data);
		while (data[index] != '.' and index < data.size())
			index++;
	}
	else
		this->data = 0;
	index++;
	int div = 10;
	for (; index < data.size(); index++)
	{
		double n = data[index] - '0';
		this->data += n / div;
		div *= 10;
	}
	
}

double Number::Get_Data()
{
	return data;
}

void Number::Show()
{
	std::cout << data;
}
