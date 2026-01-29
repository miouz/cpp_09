#include "PmergeMe.hpp"

static const size_t jacobsthal[11] = {1, 3, 5, 11, 21,
	43, 85, 171, 341, 683, 1365};

/**
 * @brief finds larger element of each pair and place it on the most right place
 * @detail it moves all numsInPair elements related to the number in pair to the most right position.
 * for example: [0, 10, 3, 5, 9] in a container of numsInPair = 2,
 * we get [0, 10] pairs [3, 5] , then we compare 10 and 5
 * since 10 > 5, we moves [0, 10] to the right of [3, 5], so the container becomes[3,5,0,10,9]
 *
 * @param nums the vector container containes all numbers
 * @param numsInPair number of elements in each pair
 */
void sortPair(std::vector<int>& nums, std::size_t numsInPair)
{
	for ( std::vector<int>::iterator secondNumInPair = nums.begin() + (numsInPair * 2 - 1);
		secondNumInPair < nums.end();
		secondNumInPair += numsInPair * 2)
	{
		std::vector<int>::iterator firstNumInPair = secondNumInPair - numsInPair;
		if (*firstNumInPair > *secondNumInPair)
		{
			std::vector<int>::iterator firstNumInFirstPair = firstNumInPair - (numsInPair - 1);
			std::vector<int>::iterator firstNumInSecondPair = secondNumInPair - (numsInPair - 1);
			std::swap_ranges(firstNumInFirstPair,
					firstNumInSecondPair, firstNumInSecondPair);
		}
	}
}

void recursiveBinaryInsertNthPair(std::vector<int>& nums, std::size_t numsInPair, std::size_t N)
{
	std::vector<int>::iterator toInsert = nums.begin() + N * numsInPair * 2 - 1;

}

/**
 * @brief insert Nth smaller group b[N] in pairs into the mainchain a , N is in jacobsthal's order
 *
 * @param nums the vector contains all numbers with all larger elements in pairs recursively sorted
 * @param numsInPair number of elements in each pair
 */
void insertion(std::vector<int>&nums, std::size_t numsInPair)
{
	size_t amountOfsmallerPair = (nums.size() / numsInPair) % 2 + (nums.size() / numsInPair) / 2;
	for (size_t index = 1; jacobsthal[index] <= amountOfsmallerPair; index++)
	{
		for (size_t NthSmallerPair = jacobsthal[index]; NthSmallerPair > jacobsthal[index - 1]; NthSmallerPair--)
		recursiveBinaryInsertNthPair(nums, numsInPair, NthSmallerPair);
	}
}

/**
 * @brief recursive Merge Insertion sort
 *
 * @param nums the actual vector contains all index of numbers
 * @param numsInPair quantities of numbers in each pair
 */
void PmergeMe::recursiveSort(std::vector<int>& nums, std::size_t numsInPair)
{
	//PRINT_TEST
	std::cout << "vector at begin of recursive:\n";
	PmergeMe::printContent(nums);

	sortPair(nums, numsInPair);

	//PRINT_TEST
	std::cout << "after sortPair:\n";
	PmergeMe::printContent(nums);
	if (nums.size() / numsInPair == 2)
		return ;
	recursiveSort(nums, numsInPair * 2);
	insertion(nums, numsInPair);
}
