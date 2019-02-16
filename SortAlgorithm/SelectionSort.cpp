#include "pch.h"
#include "SelectionSort.h"

using namespace std;
using std::vector;

#ifdef SIMPLE_SELECTION_SORT

int simple_selection_sort(std::vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		auto min = it;
		for (auto it2 = it + 1; it2 != v.end(); it2++)
		{
			if (*it2 < *min)
				min = it2;
		}
		swap(*it, *min);
	}
	return 0;
}
#endif // SIMPLE_SELECTION_SORT


#ifdef HEAP_SORT


#ifdef MAX_HEAP
// @step1
int max_heapify(vector<int> &v, size_t i) //T = O(logn)
{
	auto lc = LEFT(i); //左孩子下标(以0开头)
	auto rc = RIGHT(i); //右孩子
	size_t largest = 0;
	if (lc <= v.size() - 1 && v[lc] > v[i])
		largest = lc; //结点i,其左孩子lc,右孩子rc。局部调整复合大堆
	else
		largest = i;
	if (rc <= v.size() - 1 && v[rc] > v[largest])
		largest = rc;
	if (largest != i) // 当前最大堆的调整会影响其子结点，故递归修正
	{
		swap(v[i], v[largest]);
		max_heapify(v, largest);
	}
	else
		return 0;
}
// @step2
int build_max_heap(vector<int> &v) // T = O(n)
{
	// the bottom index of the tree-like structure
	for (size_t i = (v.size() >> 1) - 1; i != -1; i--) //i is not a negative one forever; so out of index happened
		max_heapify(v, i); //从近似完全二叉树的最后包含叶结点的根结点开始，逆序递归调整为大顶堆
	return 0;
}
// @step3
int max_heap_sort(vector<int> &v)
{
	build_max_heap(v);
	for (size_t i = v.size() - 1; i != 0; i--) // i stops 1 not 0!!!
	{//建堆后，从最后结点开始，依次交换最大最小值，且输出最大值同时重新建堆
		swap(v[0], v[i]);
		cout << v[i] << ' ';
		v.pop_back();
		max_heapify(v, 0);
	}
	cout << v[0] << endl;
	return 0;
}
#endif // MAX_HEAP


#ifdef PRIORITY_QUEUE
/*
 * 基于堆排序的优先队列算法
 * 用来维护由一组元素构成的集合S的数据结构，每个元素都有一个相关的值，称key。
 * 最大优先队列支持操作：
 * INSERT(S, x): S = S U {x};
 * MAXIMUM(S): 返回S中具有最大关键字的元素
 * EXTRACT-MAX(S): 去掉并返回S中的具有最大关键字的元素
 * INCREASE-KEYS(S, x, k): 将元素x的关键字值增加到k
 */


#endif // PRIORITY_QUEUE


#endif // HEAP_SORT
