#include "RPN.hpp"

std::string getArg(int argc, char** argv)
{
	if (argc != 2)
		throw std::invalid_argument("need 1 argument");
	std::string arg(argv[1]);
	return arg;
}

int main(int argc, char** argv)
{
	try {
		std::string arg = getArg(argc, argv);
		RPN rpn(arg);
		rpn.evaluateInput();
		std::cout << rpn.getResult() << std::endl;
	} catch (std::exception& e) {
		std::cout << "Error " << e.what() << std::endl;
	}
}

