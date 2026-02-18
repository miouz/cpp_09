#include "PmergeMe.hpp"
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
		std::cout <<"Before: ";
		PmergeMe::printContent(numsVector);
		double startVecTime = getUtime();
		PmergeMe::recursiveSort(numsVector, 1);
		double vecTime = getUtime() - startVecTime;
		std::cout <<"After:  ";
		PmergeMe::printContent(numsVector);
		std::cout << "comparaison times by using jacobsthal sequence: "
			<< count << "\n"
			<< "Time to process a range of " << argc -1 
			<< " elements with [ std::vector<int> ]" << vecTime << " microseconds"<< "\n";


		count = 0;
		std::deque<int> numsDeque;
		PmergeMe::getNumsFromArg(argc, argv, numsDeque);
		double startDeqTime = getUtime();
		PmergeMe::recursiveSort(numsDeque, 1);
		double deqTime = getUtime() - startDeqTime;
		std::cout << "Time to process a range of " << argc -1 
			<< " elements with [ std::deque<int> ]" << deqTime << " microseconds"<< "\n";

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
