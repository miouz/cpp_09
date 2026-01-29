#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <iostream>
#include <iomanip>

class PmergeMe
{
	private:
	public:
	static void recursiveSort(std::vector<int>& numAm, std::size_t numsInPair);
	template<typename T>
	static void printContent(const T& container)
	{
		for (typename T::const_iterator it = container.cbegin(); it != container.cend(); it++)
			std::cout << std::setw(5)<< *it << " ";
		std::cout << std::endl;
	}
};
#endif // !PMERGEME_HPP
