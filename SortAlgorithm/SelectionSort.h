#pragma once

#include <iostream>
#include <vector>


#ifndef SIMPLE_SELECTION_SORT
#define SIMPLE_SELECTION_SORT
//#define SIMPLE_SELECTION_SORT_TESTCASE

/*
 * 首先在未排序序列中找到最小（大）元素，存放到排序序列的起始位置
   然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
 * 最坏时间复杂度	О(n²)
   最优时间复杂度	О(n²)
   平均时间复杂度	О(n²)
   最坏空间复杂度	О(n) total, O(1) auxiliary
 */


int simple_selection_sort(std::vector<int> &v);
#endif // !SIMPLE_SELECTION_SORT


#ifndef HEAP_SORT
#define HEAP_SORT

#define MAX_HEAP
#ifdef MAX_HEAP
#define MAX_HEAP_SORT_TESTCASE
#endif // MAX_HEAP

#define PRIORITY_QUEUE
#ifdef PRIORITY_QUEUE
#define PRIORITY_QUEUE_TESTCASE
#endif // PRIORITY_QUEUE


#define LEFT(i) ((i) << 1) + 1
#define RIGHT(i) ((i) << 1) + 2
#define PARENT(i) (i - 1) >> 1

/*
 * 堆排序（英语：Heapsort）是指利用堆这种数据结构所设计的一种排序算法。
   堆是一个近似完全二叉树的结构，并同时满足堆积的性质：即子节点的键值或索引总是小于（或者大于）它的父节点。
 * 通常堆是通过一维数组来实现的。在数组起始位置为0的情形中：
   父节点i的左子节点在位置 2i+1;
   父节点i的右子节点在位置(2i+2);
   子节点i的父节点在位置 floor((i-1)/2);
 *
  最坏时间复杂度	O(n\log n)
  最优时间复杂度	O(n\log n)
  平均时间复杂度	\Theta(n\log n)
  最坏空间复杂度	O(n) total, O(1) auxiliary

 *在堆的数据结构中，堆中的最大值总是位于根节点（在优先队列中使用堆的话堆中的最小值位于根节点）。
  堆中定义以下几种操作：
  最大堆调整（Max Heapify）：将堆的末端子节点作调整，使得子节点永远小于父节点
  创建最大堆（Build Max Heap）：将堆中的所有数据重新排序
  堆排序（HeapSort）：移除位在第一个数据的根节点，并做最大堆调整的递归运算
 */

/*
 * 维护堆的性质：MAX-HEAPIFY (最大堆)
 */
int max_heapify(std::vector<int> &v, size_t i);

/*
 * 建堆:BUILD-MAX-HEAP
 */
int build_max_heap(std::vector<int> &);

/*
 * 堆排序：HEAPSORT
 */
int max_heap_sort(std::vector<int> &);

#endif // !HEAP_SORT
