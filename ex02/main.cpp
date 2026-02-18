#include "PmergeMe.hpp"
#include <vector>
#include <deque>
#include <ctime>
#include <sys/time.h>

unsigned long long getUtime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (static_cast<unsigned long long>(tv.tv_sec) * 1000000.0
		+ static_cast<unsigned long long>(tv.tv_usec));
}

int main(int argc, char** argv)
{
	try {
		count = 0;
		std::vector<int> numsVector;
		unsigned long long startVecTime = getUtime();
		PmergeMe::getNumsFromArg(argc, argv, numsVector);
		std::vector<int> copy(numsVector);
		PmergeMe::recursiveSort(numsVector, 1);
		unsigned long long vecTime = getUtime() - startVecTime;
		std::cout <<"Before: ";
		PmergeMe::printContent(copy);
		std::cout <<"After:  ";
		PmergeMe::printContent(numsVector);
		std::cout << "comparaison times by using jacobsthal sequence: "
			<< count << "\n"
			<< "Time to process a range of " << argc -1 
			<< " elements with [ std::vector<int> ]" << vecTime << " microseconds"<< "\n";


		count = 0;
		std::deque<int> numsDeque;
		unsigned long long startDeqTime = getUtime();
		PmergeMe::getNumsFromArg(argc, argv, numsDeque);
		std::vector<int> copy2(numsVector);
		PmergeMe::recursiveSort(numsDeque, 1);
		unsigned long long deqTime = getUtime() - startDeqTime;
		std::cout << "Time to process a range of " << argc -1 
			<< " elements with [ std::deque<int> ]" << deqTime << " microseconds"<< "\n";

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
