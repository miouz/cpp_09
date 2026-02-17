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

void getNumsFromArg(int argc, char **argv, std::vector<int>& nums)
{
	if (argc < 2)
		throw std::invalid_argument("need arguments");
	if (argc > jacobsthal[JACOBSTHAL_MAX - 1])
		throw std::invalid_argument("too many numbers");
	nums.reserve(argc - 1);
	for (std::size_t i = 1; argv[i]; i++)
		nums.push_back(getNumber(argv[i]));
}

int main(int argc, char** argv)
{
	try {
		std::vector<int> nums;
		getNumsFromArg(argc, argv, nums);
		PmergeMe::recursiveSort(nums, 1);
		std::cout << "SORTED:";
		PmergeMe::printContent(nums);

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
