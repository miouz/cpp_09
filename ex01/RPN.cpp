#include "RPN.hpp"

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN& other): inputStr_(other.inputStr_), numStack_(other.numStack_){}

RPN& RPN::operator=(const RPN& other)
{
	if (this == &other)
		return *this;
	numStack_ = other.numStack_;
	inputStr_ = other.inputStr_;
	return *this;
}

RPN::RPN(const std::string& inputStr): inputStr_(inputStr)
{
	if (inputStr_.empty())
		throw std::invalid_argument("empty input");
}

int RPN::getResult() const
{
	if (numStack_.empty())
		throw std::runtime_error("no result possible");
	return (numStack_.top());
}

long int RPN::operatorPlus(int a, int b) const
{
	long int result = a + b;
	if (result > std::numeric_limits<int>::max()
		|| result < std::numeric_limits<int>::min())
		throw std::out_of_range("plus operator");
	return result;
}

long int RPN::operatorMinus(int a, int b) const
{
	long int result = a - b;
	return result;
}

long int RPN::operatorMultiply(int a, int b) const
{
	long int result = a * b;
	return result;
}

long int RPN::operatorDivision(int a, int b) const
{
	if (b == 0)
		throw std::runtime_error("division by 0");
	long int result = a / b;
	return result;
}

int RPN::getNumber(const std::string& token) const
{
	return token[0] - '0';
}

void RPN::addNumber(int number)
{
	numStack_.push(number);
}

/**
 * @brief parse the token to get a valid token type
 *
 * @param token the token in string
 * @throw invalid_argument if token is not 1 char/digit
 */
RPN::TokenType RPN::getValidType(const std::string& token) const
{
	if (token.size() != 1)
		throw std::invalid_argument("");
	if (std::isdigit(token[0]))
		return NUM;
	std::string validOper[4] = {"+", "-", "*", "/"};
	RPN::TokenType type[4] = {PLUS, MINUS, MULTIPLY, DIVISION};
	for (int i = 0; i < 4; i++)
	{
		if (token == validOper[i])
			return type[i];
	}
	throw std::invalid_argument("");
}

void RPN::evaluateInput()
{
	std::istringstream input(inputStr_);
	std::string token;

	while (input >> token)
	{
		TokenType	type = getValidType(token);
		switch (type)
		{
			case NUM:
				addNumber(getNumber(token));
				break;
			case PLUS:
				evalOperatorOnStack(&RPN::operatorPlus);
				break;
			case MINUS:
				evalOperatorOnStack(&RPN::operatorMinus);
				break;
			case MULTIPLY:
				evalOperatorOnStack(&RPN::operatorMultiply);
				break;
			case DIVISION:
				evalOperatorOnStack(&RPN::operatorDivision);
				break;
		}
	}
	if (numStack_.size() != 1)
		throw std::invalid_argument("input format error");
}
