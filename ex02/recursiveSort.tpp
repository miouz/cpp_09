#ifndef RECURSIVESORT_TPP
#define RECURSIVESORT_TPP

#include <vector>
#include <set>

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
template<typename T>
void sortPair(T& nums, size_t numsInPair)
{
	size_t pairCount = nums.size() / (numsInPair * 2);
    for (size_t i = 0; i < pairCount; i++)
    {
        typename T::iterator firstNumInPair  = nums.begin() + (numsInPair - 1) + (i * numsInPair * 2);
		typename T::iterator secondNumInPair = firstNumInPair + numsInPair;
		if (*firstNumInPair > *secondNumInPair)
		{
			typename T::iterator firstNumInFirstPair = firstNumInPair - (numsInPair - 1);
			typename T::iterator firstNumInSecondPair = secondNumInPair - (numsInPair - 1);
			std::swap_ranges(firstNumInFirstPair,
					firstNumInSecondPair, firstNumInSecondPair);
		}
		firstNumInPair += numsInPair * 2;
		++count;
	}
}


/**
 * @brief init chain A, chain B and the rested numbers of this recursive level
 *
 * @param nums the current numbers
 * @param numsInPair current numbers of elements in a pair
 * @param chainAOriginal chain A
 * @param chainBOriginal chain B
 * @param rested rest once paired distributed to A and B
 */
template<typename T>
void initChainsABRested(T& nums, size_t numsInPair, T& chainAOriginal,
						 T& chainBOriginal, T& rested)
{
	size_t amountOfTotalPair = nums.size() / numsInPair;
	if (nums.size() > amountOfTotalPair * numsInPair)
		rested.insert(rested.begin(), nums.begin() + (amountOfTotalPair) * numsInPair, nums.end());

	#ifdef DEBUG
	{
		std::cout << "==========================================================================\n";
		std::cout << "nums is ";
		PmergeMe::printContent(nums);
		std::cout << "numsInPair is " << numsInPair << "\n";
		std::cout << "rested is ";
		PmergeMe::printContent(rested);
	}
	#endif


	//init chainA and B
	for (std::size_t NthPair = 0; NthPair < nums.size() / numsInPair; NthPair++)
	{
		typename T::iterator beginOnNums = nums.begin() + NthPair * numsInPair;
		typename T::iterator endOnNums = beginOnNums + numsInPair;

		if (NthPair % 2 == 0)
			chainBOriginal.insert(chainBOriginal.end(), beginOnNums, endOnNums);
		else
			chainAOriginal.insert(chainAOriginal.end(), beginOnNums, endOnNums);
	}
	//using nums as mainchain C
	nums.clear();
	//add b1 a1 to mainchain C
	nums.insert(nums.begin(), chainBOriginal.begin(), chainBOriginal.begin() + numsInPair);
	nums.insert(nums.begin() + numsInPair, chainAOriginal.begin(), chainAOriginal.begin() + numsInPair);


	#ifdef DEBUG
	{
		std::cout << "chainAOriginal:\n";
		PmergeMe::printContent(chainAOriginal);
		std::cout << "chainBOriginal:\n";
		PmergeMe::printContent(chainBOriginal);
		std::cout << "mainchain now:\n";
		PmergeMe::printContent(nums);
		std::cout << "INSERTION IN JACOBSTHAL SEQUENCE BEGIN HERE ======>\n\n";
	}
	#endif
}


template<typename T>
typename T::iterator binaryInsertNthPair( typename T::iterator toCompareB,
											   std::size_t numsInPair, T& nums, typename T::iterator end)
{
	typename T::iterator begin = nums.begin() + numsInPair - 1;
	typename T::iterator middle;
	int size = 0;
	while ((end - begin)/numsInPair > 1)
	{
		size = (end - begin)/numsInPair;
		middle = begin + (size/2) * numsInPair;
		if (*toCompareB <= *middle)
			end = middle;
		else
		 	begin = middle + numsInPair;
		++count;
	}
	if (*toCompareB <= *begin && ++count)
		return begin - (numsInPair - 1);
	else if (++count && begin != end && *toCompareB <= *end)
		return end - (numsInPair - 1);
	else
	 	return end + 1;
}


/**
 * @brief add chainA from A[NthPairInB] ~ to A[*(itJacob -1) + 1](inclus) to mainchain
 *
 * @param nums actual mainchain
 * @param numsInPair numbers of elements in a pair
 */
template<typename T>
void updateMainchain(T& nums, size_t numsInPair, size_t NthPairInB,
					 T& chainAOriginal, size_t i)
{
	size_t endOfAToSort = NthPairInB;
	//if A[N] doesn't exist
	if (chainAOriginal.size() < NthPairInB * numsInPair)
		endOfAToSort = chainAOriginal.size() / numsInPair;
	size_t beginOfAToSort = jacobsthal[i - 1] + 1;
	typename T::iterator itBeginOfAToSort = chainAOriginal.begin() + (beginOfAToSort - 1) * numsInPair;
	typename T::iterator itEndOfAToSort = chainAOriginal.begin() + endOfAToSort * numsInPair - 1; 
	nums.insert(nums.end(), itBeginOfAToSort, itEndOfAToSort + 1);
	

	#ifdef DEBUG
	{
		std::cout << "jacobsthal[i] is " << jacobsthal[i] << "\n";
		std::cout << "added A"<< beginOfAToSort <<" until A" << endOfAToSort << " to mainchain\n";
		std::cout << "to insert B"<< NthPairInB <<" until B" << jacobsthal[i - 1] + 1 << " to mainchain\n";
		std::cout << "mainchain after A added ";
		PmergeMe::printContent(nums);
		std::cout << "==========================================================================\n";
	}
	#endif
}


/**
 * @brief find A[N] or A[N-1]'s position on actual mainchain'
 *
 * @param nums actual mainchain
 * @param chainAOriginal chain A
 * @param toInsertNthPairInB B[N]
 * @param newAddedOnMainchain begin of new added A elements on Mainchain
 * @param numsInPair numbers of elements in a pair
 * @return iterator of where to stop on mainchain
 */
template<typename T>
typename T::iterator findAPosOnMain(T&nums, T& chainAOriginal,
					size_t toInsertNthPairInB, size_t newAddedOnMainchain, size_t numsInPair)
{

	//find A[N] position on mainchain nums
	typename T::iterator toCompareUntilOnA;
	typename T::iterator toCompareUntilOnMain;
	//if A[N] doesnt exist, then compare until A[N -1](inclus) on mainchain
	if (toInsertNthPairInB * numsInPair > chainAOriginal.size())
	{
		toCompareUntilOnA = chainAOriginal.end() - 1;
		toCompareUntilOnMain = std::find(nums.begin() + newAddedOnMainchain, nums.end(), *toCompareUntilOnA);

	#ifdef DEBUG
	{
		std::cout << "A" << toInsertNthPairInB << "doesnt exit:\n" << "compare using binary insertion until A" << chainAOriginal.size()/numsInPair <<" (INCLUS)"
				<< " => "<< *toCompareUntilOnMain <<"(inclus)"<< "\n";
	}
	#endif
	}
	// if A[N] exits, then compare until A[N](exclus) on mainchain
	else {
		toCompareUntilOnA = chainAOriginal.begin() + toInsertNthPairInB * numsInPair - 1;
		toCompareUntilOnMain = std::find(nums.begin() + newAddedOnMainchain, nums.end(), *toCompareUntilOnA);
		toCompareUntilOnMain -= numsInPair;
	#ifdef DEBUG
	{
		std::cout << "newAddedOnMainchain is " << newAddedOnMainchain << "\n";
		std::cout << "A" << toInsertNthPairInB << " EXIST:\n" << "compare using binary insertion BEFORE A" << *toCompareUntilOnA <<" (EXCLUS)"
				<< " => "<< *toCompareUntilOnMain <<"(inclus)"<< "\n";
	}
	#endif
	}
	return toCompareUntilOnMain;
}

/**
 * @brief split nums in 2 chain a and b, insert Nth smaller group b[N] in pairs into the main chain a , N is in jacobsthal's order
 *
 * @param nums the vector contains all numbers with all larger elements in pairs recursively sorted
 * @param numsInPair number of elements in each pair
 */
template<typename T>
void insertion(T& nums, size_t numsInPair)
{
	T rested;
	T chainAOriginal;
	T chainBOriginal;
	initChainsABRested(nums, numsInPair,chainAOriginal, chainBOriginal, rested);

	for(size_t i = 0; i < JACOBSTHAL_MAX; i++)
	{
		if (jacobsthal[i] == 1)
			continue;
		size_t NthPairInB = jacobsthal[i];
		//if less than *itJacob groups but more than *(itJacob -1)
		if (jacobsthal[i] * numsInPair > chainBOriginal.size() && (jacobsthal[i - 1]  + 1) * numsInPair <= chainBOriginal.size())
			NthPairInB = chainBOriginal.size() / numsInPair;
		//if less than &itJacob groups
		else if (jacobsthal[i] * numsInPair > chainBOriginal.size())
			break;

		size_t newAddedOnMainchain = 0;
		updateMainchain(nums, numsInPair, NthPairInB, chainAOriginal, i);
		for (size_t toInsertNthPairInB = NthPairInB; toInsertNthPairInB > jacobsthal[i - 1]; toInsertNthPairInB--)
		{
			if (toInsertNthPairInB == 1)
				break ;
			typename T::iterator	toCompareB = chainBOriginal.begin() + numsInPair *(toInsertNthPairInB - 1) + (numsInPair - 1);

			#ifdef DEBUG
			{
				std::cout << "inserting : B" <<toInsertNthPairInB 
				<< " = " << *toCompareB << "\n";
				std::cout << "numsInPair is " << numsInPair << "\n";
			}
			#endif

			typename T::iterator toCompareUntilOnMain = findAPosOnMain(nums, chainAOriginal, toInsertNthPairInB, newAddedOnMainchain, numsInPair);
			//binary research from B1, A1, A2... until A[N]-numsInPair(inclus)
			typename T::iterator toInsertOnMain = binaryInsertNthPair(toCompareB, numsInPair, nums, toCompareUntilOnMain);
		#ifdef DEBUG
			std::cout << "to insert at place of " << *toInsertOnMain << "\n";
		#endif
			if (toInsertOnMain <= nums.begin() + newAddedOnMainchain)
				newAddedOnMainchain += numsInPair;
			nums.insert(toInsertOnMain, toCompareB - (numsInPair - 1), toCompareB + 1 );
		#ifdef DEBUG
			std::cout << "after insertion of B is ";
			PmergeMe::printContent(nums);
			std::cout << "==========================================================================\n";
		#endif
		}
	}
	nums.insert(nums.end(),rested.begin(), rested.end());
}

/**
 * @brief recursive Merge Insertion sort
 *
 * @param nums the actual vector contains all index of numbers
 * @param numsInPair quantities of numbers in each pair
 */
template<typename T>
void PmergeMe::recursiveSort(T& nums, std::size_t numsInPair)
{
	sortPair(nums, numsInPair);
	if (nums.size() / numsInPair <= 2)
		return ;
	recursiveSort(nums, numsInPair * 2);
	insertion(nums, numsInPair);
}

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

template<typename T>
void PmergeMe::getNumsFromArg(int argc, char **argv, T& nums)
{
	if (argc < 2)
		throw std::invalid_argument("need arguments");
	if (argc > static_cast<int>(jacobsthal[JACOBSTHAL_MAX - 1]))
		throw std::invalid_argument("too many numbers");
	//reserveIfPossible(nums, argc - 1);
	for (std::size_t i = 1; argv[i]; i++)
		nums.push_back(getNumber(argv[i]));
	std::set<int> transfer(nums.begin(), nums.end());
	if (transfer.size() != nums.size())
		throw std::invalid_argument("duplicates are not accepted");
}

#endif
