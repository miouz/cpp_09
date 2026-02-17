#include "PmergeMe.hpp"

int getNumber(char *str)
{
	char *endptr = NULL;
	long int result = std::strtol(str, &endptr, 10);
	if (str[0] == '\0'
		||*endptr != '\0'
		|| result < 0
		|| result > std::numeric_limits<int>::max())
		throw std::invalid_argument("argument should be positif integer");
	return static_cast<int>(result);
}

int main(int argc, char** argv)
{
	try {
		std::vector<int> numsVector;
		getNumsFromArg(argc, argv, numsVector);
		PmergeMe::recursiveSort(numsVector, 1);

		std::deque<int> numsDeque;
		getNumsFromArg(argc, argv, numsVector);
		PmergeMe::recursiveSort(numsVector, 1);

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
