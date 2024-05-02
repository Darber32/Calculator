#include "Matrix.h"
#include "Calculable_Exception.h"

Matrix::Matrix(int rows, int cols, std::vector<std::vector<double>>* data)
{
	type = Type::Matrix;
	this->rows = rows;
	this->cols = cols;
	data->swap(this->data);
}

void Matrix::Show()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			std::cout << data[i][j] << " ";
		std::cout << std::endl;
	}
}

Data* Matrix::Plus(Data* b)
{
	if (b->Get_Type() == type)
	{
		Matrix* m = dynamic_cast<Matrix*>(b);
		if (rows == m->rows and cols == m->cols)
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					data[i][j] += m->data[i][j];
			return new Matrix(rows, cols, &data);
		}
		else
			throw new Calculable_Exception(Calculable_Exception_Type::Matrix_Sum);
	}
	else if (b->Get_Type() == Type::Double)
	{
		double x = dynamic_cast<Double*>(b)->Get_Data();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				data[i][j] += x;
		Matrix* m = new Matrix(rows, cols, &data);
		return m;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Matrix::Minus(Data* b)
{
	if (b->Get_Type() == type)
	{
		Matrix* m = dynamic_cast<Matrix*>(b);
		if (rows == m->rows and cols == m->cols)
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
					data[i][j] -= m->data[i][j];
			Matrix* ans = new Matrix(rows, cols, &data);
			return ans;
		}
		else
			throw new Calculable_Exception(Calculable_Exception_Type::Matrix_Diff);
	}
	else if (b->Get_Type() == Type::Double)
	{
		double x = dynamic_cast<Double*>(b)->Get_Data();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				data[i][j] -= x;
		Matrix* m = new Matrix(rows, cols, &data);
		return m;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Matrix::Multiplication(Data* b)
{
	if (b->Get_Type() == type)
	{
		Matrix* m = dynamic_cast<Matrix*>(b);
		if (cols == m->rows)
		{
			int rows = this->rows, cols = m->cols;
			std::vector<std::vector<double>> new_data;
			new_data.resize(rows);
			for (int i = 0; i < rows; i++)
				new_data[i].resize(cols);
			for (int i = 0; i < this->rows; i++)
			{
				for (int j = 0; j < m->cols; j++)
				{
					new_data[i][j] = 0;
					for (int k = 0; k < this->cols; k++)
						new_data[i][j] += data[i][k] * m->data[k][j];
				}
			}
			Matrix* ans = new Matrix(rows, cols, &new_data);
			return ans;
		}
		else
			throw new Calculable_Exception(Calculable_Exception_Type::Matrix_Mult);
	}
	else if (b->Get_Type() == Type::Double)
	{
		Matrix* m = new Matrix(rows, cols, &data);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				m->data[i][j] *= dynamic_cast<Double*>(b)->Get_Data();
		return m;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Matrix::Division(Data* b)
{
	if (b->Get_Type() == Type::Double)
	{
		double x = dynamic_cast<Double*>(b)->Get_Data();
		if (x == 0)
			throw new Calculable_Exception(Calculable_Exception_Type::Division_By_Zero);
		Matrix* m = new Matrix(rows, cols, &data);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				m->data[i][j] /= x;
		return m;
	}
	if (b->Get_Type() == type)
		throw new Calculable_Exception(Calculable_Exception_Type::Matrix_Div);
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}

Data* Matrix::Exponentiation(Data* b)
{
	if (b->Get_Type() == Type::Double)
	{
		Matrix* m = new Matrix(rows, cols, &data);
		int indicator = static_cast<int>(dynamic_cast<Double*>(b)->Get_Data());
		if (indicator < 0)
			throw new Calculable_Exception(Calculable_Exception_Type::Negative_Indicator);
		else if (indicator == 0)
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++)
				{
					if (i == j)
						m->data[i][j] = 1;
					else
						m->data[i][j] = 0;
				}
		else
		{
			int c = 1;
			while (c < indicator)
			{
				Matrix* temp = m;
				m = dynamic_cast<Matrix*>(m->Multiplication(this));
				delete temp;
				c++;
			}
		}
		return m;
	}
	throw new Calculable_Exception(Calculable_Exception_Type::Type_Mismatch);
}
