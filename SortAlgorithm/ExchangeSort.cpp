#include "pch.h"
#include "ExchangeSort.h"

using namespace std;
using std::vector;

#ifdef BUBBLE_SORT

int bubble_sort(vector<int> &v)
{
	for (vector<int>::size_type i = 0; i != v.size() - 1; i++)
	{
		for (auto it = v.begin(); it != v.end() - i - 1; it++) //TYPE:vector<int>::iterator
		{
			if (*it > *(it + 1))
				swap(*it, *(it + 1));
		}
	}
	return 0;
}
#endif // BUBBLE_SORT


#ifdef QUICK_SORT
//递归版本
int quick_sort_recursive(vector<int> &v, vector<int>::iterator begin, vector<int>::iterator tail)
{
	if (begin >= tail)
		return 0;
	auto pivot = tail;
	auto left = begin, right = tail - 1;
	while (left < right)
	{
		while (*left < *pivot && left < right)
			left++;
		while (*right >= *pivot && left < right)
			right--;
		swap(*left, *right);
	}
	if (*left >= *pivot)
		swap(*left, *pivot);
	else
		left++;
	if (begin != left)
		quick_sort_recursive(v, begin, left - 1);  // Trouble Case: when left-1 < begin that out of vector's range.
	if (tail != left)
		quick_sort_recursive(v, left + 1, tail);
	if (begin == left || tail == left)
		return 0;
}
#endif // QUICK_SORT
