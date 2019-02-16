#pragma once
#include <iostream>
#include <queue>

#ifndef BINARY_TREE
#define BINARY_TREE

typedef int data_t;
struct node
{
	data_t data;
	node* lchild;
	node* rchild;
};
//先序遍历的递归实现
int pre_order(node* &root);
//中序遍历递归实现
int in_order(node* &root);
//后序遍历递归实现
int post_order(node* &root);
//层序遍历队列实现
int layer_order(node* &root);

/* 
 * 
 * void CreateBiTree(BiTree &T)
 * {
 *	 char ch;
 *	 cin>>ch;
 *	 if(ch=='#') 
 *		 T=NULL;
 *	 else
 *	 {
 *		 T= new BiTreeNode;
 *		 if(!T) exit(0);
 *		 T->data=ch; 
 *		 CreateBiTree(T->lchild);  
 *		 CreateBiTree(T->rchild); 
 *	 }
 * 使用此方式要求使用者"以一种正确的方式"来完全的输入合适数量的#表示空树来完成整个二叉树的构建，很是不便。
 */

//使用先序序列和中序序列来构建二叉树
node* createbt(int PreL, int PreR, int inL, int inR);

#endif // !BINARY_TREE
