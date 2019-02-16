#pragma once

#include <iostream>
#include <vector>

#ifndef MERGE_SORT
#define MERGE_SORT

#define MERGE_SORT_TESTCASE

/*
 * 归并排序（英语：Merge sort，或mergesort），是创建在归并操作上的一种有效的排序算法，效率为 O(n logn)
 * 该算法是采用分治法（Divide and Conquer）的一个非常典型的应用，且各层分治递归可以同时进行。
 * 
 */
int merge_sort(std::vector<int> &v);
#endif // !MERGE_SORT
