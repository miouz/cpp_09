#include "PmergeMe.hpp"
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
		PmergeMe::getNumsFromArg(argc, argv, numsVector);
		std::cout << argc - 1 <<" integers before sorting :\n";
		PmergeMe::printContent(numsVector);
		double startVecTime = getUtime();
		PmergeMe::recursiveSort(numsVector, 1);
		double vecTime = getUtime() - startVecTime;
		std::cout << "sorted with [std::vector<int>] :\n";
		PmergeMe::printContent(numsVector);
		std::cout << "comparaison times by using jacobsthal sequence: "
			<< count << "\n"
			<< "time to process sorting: " << vecTime << " microseconds"<< "\n";
		std::cout << "\n===================================================\n\n";


		count = 0;
		std::deque<int> numsDeque;
		PmergeMe::getNumsFromArg(argc, argv, numsDeque);
		std::cout << argc - 1 << " integers before sorting :\n";
		PmergeMe::printContent(numsDeque);
		double startDeqTime = getUtime();
		PmergeMe::recursiveSort(numsDeque, 1);
		double deqTime = getUtime() - startDeqTime;
		std::cout << "sorted with [std::deque<int>] :\n";
		PmergeMe::printContent(numsDeque);
		std::cout << "comparaison times by using jacobsthal sequence: "
			<< count << "\n"
			<< "time to process sorting: " << deqTime << " microseconds"<< "\n\n";

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
