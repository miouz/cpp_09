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
		PLUS,
		MINUS,
		MULTIPLY,
		DIVISION,
		NUM
	};

	std::string inputStr_;
	std::stack<int> numStack_;

	RPN();
	int getNumber(const std::string& token) const;
	void addNumber(int number);
	TokenType getValidType(const std::string& token) const;

	template<typename Func>
	void evalOperatorOnStack(Func operatorFunc)
	{
		if (numStack_.size() < 2)
			throw std::runtime_error("no suffisant numbers to applay operator");
		int last = numStack_.top();
		numStack_.pop();
		long int result =(this->*operatorFunc)(numStack_.top(), last);
		if (result > std::numeric_limits<int>::max()
			|| result < std::numeric_limits<int>::min())
			throw std::out_of_range("overflow or underflow occured");
		numStack_.top() = static_cast<int>(result);
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
