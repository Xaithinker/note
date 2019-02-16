#include "pch.h"
#include "InsertionAlgorithm.h"

using namespace std;
using std::vector;

#ifdef INSERTION_SORT

int insertion_sort(int arr[], int len)
{
	for (int i = 1; i < len; i++)
	{
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && key < arr[j])
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
	return 0;
}


#endif // INSERTION_SORT


#ifdef BINARY_INSERTION_SORT

int binary_insertion_sort(vector<int> &v)
{
	auto begin = v.begin();

	auto key = begin + 1;
	auto end = key;
	auto mid = begin + (end - begin) / 2;

	for (auto it = v.begin() + 1; it != v.end(); it++)
	{
		while (end != mid)
		{
			if (*key < *mid)
				end = mid;
			else
				begin = mid + 1;
			mid = begin + (end - begin) / 2;
		}
		// 移动元素
		auto temp = *key;
		for (auto it = key; it != begin; it--)
		{
			*it = *(it - 1);
		}
		* mid = temp;
		//下一次循环值
		key++;
		end = key;
	}
	return 0;
}

#endif // BINARY_INSERTION_SORT


#ifdef SHELL_SORT
/*
 * 
 伪代码：
    input: an array a of length n with array elements numbered 0 to n − 1
    inc <- round(n/2)
    while inc > 0 do:    
        for i = inc .. n − 1 do:        
            temp <- a[i]        
            j <- i        
            while j ≥ inc and a[j − inc] > temp do:            
                a[j] <- a[j − inc]            
                j <- j − inc        
            a[j] <- temp    
        inc <- round(inc / 2)
 *
 */

int shell_sort(vector<int> &v)
{
	vector<int>::size_type gap = v.size() / 2;
	while (gap != 0)
	{
		for (vector<int>::size_type i = gap; i != v.size(); i++)
		{
			auto temp = v[i];
			auto j = i;
			while (j >= gap && v[j-gap] > temp)
			{
				v[j] = v[j - gap];
				j = j - gap;
			}
			v[j] = temp;
		}
		gap /= 2;	
	}
	return 0;
}
#endif // SHELL_SORT
