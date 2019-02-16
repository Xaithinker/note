#include "pch.h"
#include "InsertionAlgorithm.h"
#include "ExchangeSort.h"
#include "SelectionSort.h"

using namespace std;
using std::vector;

int main()
{

#ifdef INSERTION_SORT_TESTCASE
	int arr[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	int len = 10;
	if (!insertion_sort(arr, len))
		testcase("insertion_sort");
	for (auto it = begin(arr); it != end(arr); it++)
		cout << *it << ' ';
	cout << endl;
#endif // INSERTION_SORT_TESTCASE

#ifdef BINARY_INSERTION_SORT_TESTCASE
	vector<int> v1{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	vector<int> &ref_v1 = v1;
	if (!binary_insertion_sort(ref_v1))
		testcase("binary_insertion_sort");
	for (auto i : v1)
		cout << i << ' ';
	cout << endl;

#endif // BINARY_INSERTION_SORT_TESTCASE

#ifdef SHELL_SORT_TESTCASE
	vector<int> v2{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	vector<int> &v2_ref = v2;
	if (!shell_sort(v2_ref))
		testcase("shell_sort");
	for (auto i : v2)
		cout << i << ' ';
	cout << endl;
#endif // SHELL_SORT_TESTCASE

#ifdef BUBBLE_SORT_TESTCASE
	vector<int> v3{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	vector<int> &v3_ref = v3;
	if (!bubble_sort(v3_ref))
		testcase("bubble_sort");
	for (auto i : v3)
		cout << i << ' ';
	cout << endl;
#endif // BUBBLE_SORT_TESTCASE

#ifdef QUICK_SORT_TESTCASE
	vector<int> v4{ 5, 6, 9, 8, 7, 4, 3, 2, 1, 0 };
	vector<int> &v4_ref = v4;
	vector<int>::iterator begin = v4_ref.begin();
	vector<int>::iterator tail = v4_ref.end() - 1;
	if (!quick_sort_recursive(v4_ref, begin, tail))
		testcase("quick_sort_recursive");
	for (auto i : v4)
		cout << i << ' ';
	cout << endl;
#endif // QUICK_SORT_TESTCASE

#ifdef SIMPLE_SELECTION_SORT_TESTCASE
	vector<int> v5{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	vector<int> &v5_ref = v5;
	if (!simple_selection_sort(v5_ref))
		testcase("simple_selection_sort");
	for (auto i : v5)
		cout << i << ' ';
	cout << endl;
#endif // SIMPLE_SELECTION_SORT_TESTCASE

#ifdef MAX_HEAP_SORT_TESTCASE
	vector<int> v6 { 9, 5, 2, 1, 3, 6, 7, 8, 4, 0, 15, 98, 111, 100000, -1 };
	vector<int> &v6_ref = v6;
	max_heap_sort(v6_ref);
#endif // MAX_HEAP_SORT_TESTCASE

#ifdef PRIORITY_QUEUE_TESTCASE
	// pass
#endif // PRIORITY_QUEUE_TESTCASE

#ifdef MERGE_SORT_TESTCASE

#endif // MERGE_SORT_TESTCASE

	system("pause");
	return 0;
}
