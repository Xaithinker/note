#pragma once
#include <iostream>
#include <string>
#include <vector>

#define TEST
#ifdef TEST
#define testcase(name) cout << name << " test passed!" << endl; 
#endif // TEST


#ifndef INSERTION_SORT
#define INSERTION_SORT
//#define INSERTION_SORT_TESTCASE //Open for main()
/*
 * 插入排序在实现上，通常采用in-place排序
 * 在从后向前扫描过程中，需要反复把已排序元素逐步向后挪位，为最新元素提供插入空间。
 * 最坏时间复杂度	O(n^2)
 * 最优时间复杂度	O(n)
 * 平均时间复杂度	O(n^2)
 * 最坏空间复杂度	总共 O(n) ，需要辅助空间 O(1)
 */

int insertion_sort(int arr[], int len);

#endif // !INSERTION_SORT


#ifndef BINARY_INSERTION_SORT
#define BINARY_INSERTION_SORT
//#define BINARY_INSERTION_SORT_TESTCASE  //Open for main()
/*
 * 二分插入排序(折半插入)：采用二分查找法在比较操作上减少数目
 * 
 */

// 二分查找位置key
int binary_insertion_sort(std::vector<int> &v);

#endif // !BINARY_INSERTION_SORT


#ifndef SHELL_SORT
#define SHELL_SORT
//#define SHELL_SORT_TESTCASE  //Open for main()
/*
 * 希尔排序，也称递减增量排序算法，是插入排序的一种更高效的改进版本。希尔排序是非稳定排序算法。
 * 希尔排序是基于插入排序的以下两点性质而提出改进方法的：
 * 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率;
 * 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位;

 * 算法实现：希尔排序通过将比较的全部元素分为几个区域来提升插入排序的性能。
   这样可以让一个元素可以一次性地朝最终位置前进一大步。
   然后算法再取越来越小的步长进行排序，算法的最后一步就是普通的插入排序，
   但是到了这步，需排序的数据几乎是已排好的了（此时插入排序较快）。


   步长序列	最坏情况下复杂度
    n/2^i         O(n^2)
    2^k - 1       O(n^{3/2})
	2^i 3^j       O( n\log^2 n )
 */

int shell_sort(std::vector<int> &v);
#endif // !SHELL_SORT
