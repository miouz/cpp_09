#include "PmergeMe.hpp"
#include <bits/types/struct_timeval.h>
#include <cstddef>
#include <vector>
#include <deque>
#include <ctime>
#include <sys/time.h>

double getUtime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

int main(int argc, char** argv)
{
	try {
		count = 0;
		std::vector<int> numsVector;
		double startTime = getUtime();
		PmergeMe::getNumsFromArg(argc, argv, numsVector);
		std::cout << "integer sequence before sorting :\n";
		PmergeMe::printContent(numsVector);
		PmergeMe::recursiveSort(numsVector, 1);
		std::cout << "sorted with [std::vector<int>] :\n";
		PmergeMe::printContent(numsVector);
		std::cout << "comparaison times by using jacobsthal sequence: "
			<< count << "\n";
		std::cout << "\n===================================================\n\n";


		count = 0;
		std::deque<int> numsDeque;
		PmergeMe::getNumsFromArg(argc, argv, numsDeque);
		std::cout << "integer sequence before sorting :\n";
		PmergeMe::printContent(numsDeque);
		PmergeMe::recursiveSort(numsDeque, 1);
		std::cout << "sorted with [std::deque<int>] :\n";
		PmergeMe::printContent(numsDeque);
		std::cout << "comparaison times by using jacobsthal sequence: "
			<< count << "\n\n";

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
