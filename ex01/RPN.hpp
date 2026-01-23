#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <sstream>

class RPN
{
private:
	enum TokenType
	{
		NUM,
		PLUS,
		MINUS,
		MULTIPLY,
		DIVISION
	};

	std::string inputStr_;
	std::stack<int> numStack_;

	RPN();
	int getNumber(const std::string& token);
	void addNumber(int number);
	TokenType getType(const std::string& token);

	template<typename Func>
	void evalOperatorOnStack(Func operatorFunc)
	{
		if (numStack_.size() < 2)
			throw std::runtime_error("less than 2 numbers rest");
		int last = numStack_.top();
		numStack_.pop();
		numStack_.top() = static_cast<int>(operatorFunc(numStack_.top(), last));
	}
public:
	RPN(const std::string& inputStr);
	~RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN&other);

	void evaluateInput();
	int	getResult() const;
	long int operatorPlus(int a, int b) const;
	long int operatorMinus(int a, int b) const;
	long int operatorMultiply(int a, int b) const;
	long int operatorDivision(int a, int b) const;
};
#endif // !RPN_HPP
