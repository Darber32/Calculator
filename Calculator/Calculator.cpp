﻿#include <iostream>
#include "fstream"
#include <list>
#include "Token.h"
#include "Number.h"
#include "Variable.h"
#include "Operation.h"
#include "Bracket.h"
#include "Double.h"
#include "Fraction.h"
#include "Matrix.h"
#include "Formula_Exception.h"
#include "Calculable_Exception.h"
#include "json.hpp"

class Calculator
{
private:
    std::list<Token*> token_arr, rpn, stack;
    std::list <Data*> ans;

    void Make_Arr(std::string s, int key)
    {
        nlohmann::json json;
        if (key == 3)
        {
            std::fstream file;
            file.open(s);
            if (not file)
            {
                throw new Formula_Exception(Formula_Exception_Type::Wrong_File);
            }
            file >> json;
            file.close();
            s = json["formula"];
        }
        std::erase(s, ' ');
        std::string num, var;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '.' or s[i] >= '0' and s[i] <= '9')
            {
                num.push_back(s[i]);
                if (s[i + 1] != '.' and (s[i + 1] < '0' or s[i + 1] > '9'))
                {
                    Number* n = new Number(num);
                    token_arr.push_back(n);
                    num.clear();
                }
            }
            else if (s[i] == '+' or s[i] == '-' or s[i] == '*' or s[i] == '^' or s[i] == '/')
            {
                Operation* o = new Operation(s[i]);
                token_arr.push_back(o);
            }
            else if (s[i] == '(' or s[i] == ')')
            {
                Bracket* b = new Bracket(s[i]);
                token_arr.push_back(b);
            }
            else if (s[i] >= 'A' and s[i] <= 'Z' or s[i] >= 'a' and s[i] <= 'z')
            {
                var.push_back(s[i]);
                if ((s[i + 1] < 'A' or s[i + 1] > 'Z') and (s[i + 1] < 'a' or s[i + 1] > 'z'))
                {
                    Data* data = nullptr;;
                    double x;
                    int a, b, rows, cols;
                    std::vector<std::vector<double>> arr;
                    switch (key)
                    {
                    case 0:
                        std::cout << "Введите значение переменной " << var << ": ";
                        std::cin >> x;
                        data = new Double(x);
                        break;
                    case 1:
                        std::cout << "Введите значение числителя переменной " << var << ": ";
                        std::cin >> a;
                        std::cout << "Введите значение знаменателя переменной " << var << ": ";
                        std::cin >> b;
                        data = new Fraction(a, b);
                        break;
                    case 2:
                        do
                        {
                            std::cout << "Введите количество строк для переменной " << var << ": ";
                            std::cin >> rows;
                        } while (rows < 1);
                        do
                        {
                            std::cout << "Введите количество столбцов для переменной " << var << ": ";
                            std::cin >> cols;
                        } while (cols < 1);
                        arr.resize(rows);
                        for (int i = 0; i < rows; i++)
                            arr[i].resize(cols);
                        for (int i = 0; i < rows; i++)
                        {
                            for (int j = 0; j < cols; j++)
                            {
                                double x;
                                std::cout << "Введите " << j + 1 << " элемент " << i + 1 << " строки для переменной " << var << ": ";
                                std::cin >> x;
                                arr[i][j] = x;
                            }
                        }
                        data = new Matrix(rows, cols, &arr);
                        break;
                    case 3:
                    {
                        bool flag = false;
                        for (auto i : json["variables"])
                        {
                            if (i["name"] == var)
                            {
                                flag = true;
                                int x = i["type"];
                                switch (x)
                                {
                                case 0:
                                    data = new Double(i["value"]);
                                    break;
                                case 1:
                                    data = new Fraction(i["value"]["num"], i["value"]["denom"]);
                                    break;
                                case 2:
                                    rows = i["value"]["rows"];
                                    cols = i["value"]["cols"];
                                    for (auto i : i["value"]["data"])
                                    {
                                        std::vector<double> row;
                                        for (auto j : i)
                                            row.push_back(j);
                                        if (row.size() != cols)
                                            throw new Calculable_Exception(Calculable_Exception_Type::Wrong_Matrix);
                                        arr.push_back(row);
                                    }
                                    if (arr.size() != rows)
                                        throw new Calculable_Exception(Calculable_Exception_Type::Wrong_Matrix);
                                    data = new Matrix(rows, cols, &arr);
                                }
                                break;
                            }
                        }
                        if (not flag)
                        {
                            throw new Calculable_Exception(Calculable_Exception_Type::No_Operand);
                        }
                    }
                    }
                    Variable* v = new Variable(var, data);
                    token_arr.push_back(v);
                    var.clear();
                }
            }
            else
                throw new Formula_Exception(Formula_Exception_Type::Unexpected_Symbol);
        }
        std::list<Token*>::iterator i = token_arr.begin();
        while (i != token_arr.end())
        {
            Token* prev = *i; 
            i++;
            if (i != token_arr.end())
            {
                Token* cur = *i;
                if (prev->Get_Type() == Token_Type::Number or prev->Get_Type() == Token_Type::Variable or 
                    (prev->Get_Type() == Token_Type::Bracket and static_cast<Bracket*>(prev)->Get_Bracket_Type() == ')'))
                {
                    if (cur->Get_Type() == Token_Type::Number or cur->Get_Type() == Token_Type::Variable or 
                        (cur->Get_Type() == Token_Type::Bracket and static_cast<Bracket*>(cur)->Get_Bracket_Type() == '('))
                        throw new Formula_Exception(Formula_Exception_Type::No_Operation);
                }
            }
        }
    }

    void Make_RPN()
    {
        while (not token_arr.empty())
        {
            Token* tok = token_arr.front();
            token_arr.pop_front();
            switch (tok->Get_Type())
            {
            case Token_Type::Number:
                rpn.push_back(tok);
                break;
            case Token_Type::Variable:
                rpn.push_back(tok);
                break;
            case Token_Type::Bracket:
                if (static_cast<Bracket*>(tok)->Get_Bracket_Type() == '(')
                {
                    stack.push_back(tok);
                }
                else
                {
                    if (stack.empty())
                        throw new Formula_Exception(Formula_Exception_Type::Bracket_Mismatch);
                    while (rpn.back()->Get_Type() != Token_Type::Bracket)
                    {
                        rpn.push_back(stack.back());
                        stack.pop_back();
                        if (stack.empty())
                            throw new Formula_Exception(Formula_Exception_Type::Bracket_Mismatch);
                    }
                    delete rpn.back();
                    rpn.pop_back();
                    delete tok;
                }
                break;
            case Token_Type::Operation:
                Operation* operation = static_cast<Operation*>(tok);
                if (not stack.empty())
                {
                    if (stack.back()->Get_Type() == Token_Type::Operation)
                    {
                        Operation* prev = static_cast<Operation*>(stack.back());
                        while (operation->Get_Priority() <= prev->Get_Priority() and not stack.empty())
                        {
                            rpn.push_back(prev);
                            stack.pop_back();
                            if (not stack.empty() and stack.back()->Get_Type() == Token_Type::Operation)
                                prev = static_cast<Operation*>(stack.back());
                        }
                    }
                }
                stack.push_back(tok);
                break;

            }
        }
        while (not stack.empty())
        {
            if (stack.back()->Get_Type() == Token_Type::Bracket)
                throw new Formula_Exception(Formula_Exception_Type::Bracket_Mismatch);
            rpn.push_back(stack.back());
            stack.pop_back();
        }
}


    Data* Calculate()
    {
        //for (auto i : rpn)
        //    i->Show();
        //std::cout << std::endl;
        Token* temp = nullptr;
        while (not rpn.empty())
        {
            switch (rpn.front()->Get_Type())
            {
            case Token_Type::Number:
                ans.push_back(new Double(static_cast<Number*>(rpn.front())->Get_Data()));
                temp = rpn.front();
                rpn.pop_front();
                break;
            case Token_Type::Variable:
                ans.push_back(static_cast<Variable*>(rpn.front())->Get_Data());
                temp = rpn.front();
                rpn.pop_front();
                break;
            case Token_Type::Operation:
                Data* first, *second, * new_data;
                if (ans.empty())
                    throw new Formula_Exception(Formula_Exception_Type::Lack_Of_Operands);
                second = ans.back();
                ans.pop_back();
                if (ans.empty())
                    throw new Formula_Exception(Formula_Exception_Type::Lack_Of_Operands);
                first = ans.back();
                ans.pop_back();
                Operation* operation = static_cast<Operation*>(rpn.front());
                temp = rpn.front();
                rpn.pop_front();
                switch (operation->Get_Operation_Type())
                {
                case '+':
                    new_data = first->Plus(second);
                    break;
                case '-':
                    new_data = first->Minus(second);
                    break;
                case '*':
                    new_data = first->Multiplication(second);
                    break;
                case '/':
                    new_data = first->Division(second);
                    break;
                case '^':
                    new_data = first->Exponentiation(second);
                    break;
                }
                delete first;
                delete second;
                ans.push_back(new_data);
                break;
            }
            if (temp != nullptr)
                delete temp;
        }
        return ans.front();
    }

    void Clear()
    {
        if (not token_arr.empty())
        {
            for (auto i : token_arr)
                delete i;
            token_arr.clear();
        }
        if (not rpn.empty())
        {
            for (auto i : rpn)
                delete i;
            rpn.clear();
        }
        if (not stack.empty())
        {
            for (auto i : stack)
                delete i;
            stack.clear();
        }
        if (not ans.empty())
        {
            for (auto i : ans)
                delete i;
            ans.clear();
        }
    }

public:
    ~Calculator()
    {
        Clear();
    }
    Data* Calculate(std::string s, int key)
    {
        try
        {
            Clear();
            Make_Arr(s, key);
            Make_RPN();
            return Calculate();
        }
        catch (Exception* e)
        {
            Clear();
            Formula_Exception* fe;
            Calculable_Exception* ce;
            switch (e->Get_Type())
            {
            case Exception_Type::Formula_Exception:
                std::cout << "Формула введена неверно: ";
                fe = static_cast<Formula_Exception*>(e);
                switch (fe->Get_Exception_Type())
                {
                case Formula_Exception_Type::Bracket_Mismatch:
                    std::cout << "несоответствие скобок.";
                    break;
                case Formula_Exception_Type::Lack_Of_Operands:
                    std::cout << "недостаток операндов.";
                    break;
                case Formula_Exception_Type::No_Operation:
                    std::cout << "отсутствие операции между операндами.";
                    break;
                case Formula_Exception_Type::Unexpected_Symbol:
                    std::cout << "неожиданный символ.";
                    break;
                case Formula_Exception_Type::Wrong_File:
                    std::cout << "файл не найден.";
                    break;
                }
                std::cout << std::endl;
                delete e;
                std::cout << "1 - вещественные числа" << std::endl << "2 - дробные числа" << std::endl << "3 - матрицы" << std::endl << "4 - взять из файла" << std::endl;
                std::cin >> key;
                if (key != 4)
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Введите формулу: ";
                    std::getline(std::cin, s);
                }
                else
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Введите название файла: ";
                    std::getline(std::cin, s);
                }
                return Calculate(s, key - 1);
                break;
            case Exception_Type::Calculable_Exception:
                    std::cout << "Ошибка в вычислении: ";
                    ce = static_cast<Calculable_Exception*>(e);
                    switch (ce->Get_Exception_Type())
                    {
                    case Calculable_Exception_Type::Division_By_Zero:
                        std::cout << "обнаружено деление на ноль.";
                        break;
                    case Calculable_Exception_Type::Type_Mismatch:
                        std::cout << "обнаружено несоответствие типов.";
                        break;
                    case Calculable_Exception_Type::Matrix_Sum:
                        std::cout << "сложение матриц невозможно: разное количество строк и/или столбцов.";
                        break;
                    case Calculable_Exception_Type::Matrix_Diff:
                        std::cout << "вычитание матриц невозможно: разное количество строк и/или столбцов.";
                        break;
                    case Calculable_Exception_Type::Matrix_Mult:
                        std::cout << "умножение матриц невозможно: разное количество строк первой матрицы и столбцов второй матрицы.";
                        break;
                    case Calculable_Exception_Type::Matrix_Div:
                        std::cout << "обнаружено деление на матрицу.";
                        break;
                    case Calculable_Exception_Type::Negative_Indicator:
                        std::cout << "обнаружено возведение в степень, показатель которой меньше 0";
                        break;
                    case Calculable_Exception_Type::Wrong_Matrix:
                        std::cout << "параметры матрицы даны неверно.";
                        break;
                    case Calculable_Exception_Type::No_Operand:
                        std::cout << "в формуле отсутствует операнд.";
                        break;
                    }
                    delete e;
                    exit(0);
                    break;
            }
        }
    }
};

int main()
{
    system("chcp 1251 > null");
    std::string task;
    int key;
    std::cout << "1 - вещественные числа" << std::endl << "2 - дробные числа" << std::endl << "3 - матрицы" << std::endl << "4 - взять из файла" << std::endl;
    std::cin >> key;
    if (key != 4)
    {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите формулу: ";
    std::getline(std::cin, task);
    }
    else
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Введите название файла: ";
        std::getline(std::cin, task);
    }
    Calculator calc;
    Data* ans = calc.Calculate(task, key - 1);
    std::cout << "Ответ: ";
    if (ans->Get_Type() == Type::Matrix)
        std::cout << std::endl;
    ans->Show();
}

//3 + 4 * 2 / (1 - 5)^2
