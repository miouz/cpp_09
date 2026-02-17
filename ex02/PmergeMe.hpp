#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <iostream>
#include <iomanip>

static const size_t JACOBSTHAL_MAX = 19;

static size_t jacobsthal[JACOBSTHAL_MAX]= {1, 3, 5, 11, 21, 43,
	85, 171, 341, 683, 1365, 2731, 5461,
	10923, 21845, 43691, 87381, 174763, 349525};

static size_t count = 0;

class PmergeMe
{
	private:
	public:
	template<typename T>
	static void recursiveSort(T& num, std::size_t numsInPair);
	template<typename T>
	static void printContent(const T& container)
	{
		for (typename T::const_iterator it = container.cbegin(); it != container.cend(); it++)
			std::cout << std::setw(5)<< *it << " ";
		std::cout << std::endl;
	}
};

#include "recursiveSort.tpp"
#endif // !PMERGEME_HPP
