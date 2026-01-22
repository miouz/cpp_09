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

RPN::RPN(const std::string& inputStr)
{
	std::string::const_iterator it = inputStr.cbegin();


}
