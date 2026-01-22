#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>

class RPN
{
private:
	std::stack<int> numStack_;
	int	result_;

	void addNumber(const int number);
	void operatorEval(const char op);
	RPN();

public:
	RPN(const std::string& inputStr);
	~RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN&other);

	int	getResult() const;
};
#endif // !RPN_HPP
