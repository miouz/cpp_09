#include "RPN.hpp"

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN& other): numStack_(other.numStack_) {}

RPN& RPN::operator=(const RPN& other)
{
	if (this == &other)
		return *this;
	numStack_ = other.numStack_;
	return *this;
}

RPN::RPN(const std::string& inputStr): inputStr_(inputStr)
{
	if (inputStr_.empty())
		throw std::invalid_argument("empty input");
}

int RPN::getResult() const
{
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
	if (result > std::numeric_limits<int>::max()
		|| result < std::numeric_limits<int>::min())
		throw std::out_of_range("minus operator");
	return result;
}

long int RPN::operatorMultiply(int a, int b) const
{
	long int result = a * b;
	if (result > std::numeric_limits<int>::max()
		|| result < std::numeric_limits<int>::min())
		throw std::out_of_range("multiply operator");
	return result;
}

long int RPN::operatorDivision(int a, int b) const
{
	if (b == 0)
		throw std::invalid_argument("division by 0");
	long int result = a * b;
	if (result > std::numeric_limits<int>::max()
		|| result < std::numeric_limits<int>::min())
		throw std::out_of_range("minus operator");
	return result;
}

void RPN::evaluateInput()
{
	std::istringstream input(inputStr_);
	std::string token;

	while (input >> token)
	{
		TokenType	type = getType(token);
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
