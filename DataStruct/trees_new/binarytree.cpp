#include "pch.h"
#include "binarytree.h"

using namespace std;

const extern int maxn;
extern int pre[], in[], post[];

#ifdef BINARY_TREE
//二叉树先序遍历
int pre_order(node* &root)
{
	if (root == nullptr)return 0;
	cout << root->data;
	pre_order(root->lchild);
	pre_order(root->rchild);
	return 0;
}
//二叉树中序遍历
int in_order(node* &root)
{
	if (root == nullptr)return 0;
	in_order(root->lchild);
	cout << root->data;
	in_order(root->rchild);
	return 0;
}
int post_order(node* &root)
{
	if (root == nullptr)return 0;
	in_order(root->lchild);
	in_order(root->rchild);
	cout << root->data;
	return 0;
}
int layer_order(node* &root)
{//使用队列实现类似BFS搜索的层序遍历
	queue<node*> q; //队列存地址
	q.push(root); //根结点入队
	while (!q.empty())
	{
		node* now = q.front(); //取出队首元素
		q.pop(); //出队
		cout << now->data;
		if (now->lchild != nullptr)q.push(now->lchild);
		if (now->rchild != nullptr)q.push(now->rchild);
	}
	return 0;
}

/*             使用先序和中序来构建二叉树：原理
 * 层序序列: 单独分析

 *           ------左子树------    -----右子树-----    根
 * 后序序列: pos1 pos2 ...   posk  posk+1 ....posn-1   posn


 *           根    -----左子树-------   -----右子树------
 * 先序序列: preL pre2 pre3 ......prek   prek+1 ..... preR


 * 中序序列: inL  in2 in3 ..ink-1 ink    ink+1 ...    inR
 *           --------左子树------  根   ------右子树------
 * 以先序和中序为例：
 * preL == ink ---->找到k
 * 根据中序得知左子树结点个数 numberLeft = k - inL
 * 先序:左子树区间[preL+1, preL + numberLeft] 右子树区间 [preL+numberLeft + 1, preR]
 * 中序:左子树区间[inL, k-1] 右子树区间[k+1, inR]
 */

node* createbt(int PreL, int PreR, int inL, int inR)
{
	if (PreL > PreR)return nullptr;
	node* root = new node;//创建二叉树根结点
	root->data = pre[PreL]; //根结点值域
	int k;
	for (k = inL; k <= inR; k++)
		if (in[k] == pre[PreL])break;//寻找中序中的根，以便区分左子树和右子树
	int numLeft = k - inL; //左子树的结点个数

	//返回左子树根结点，递归。
	root->lchild = createbt(PreL + 1, PreL + numLeft, inL, k - 1);
	//返回右子树根结点，递归。
	root->rchild = createbt(PreL + numLeft + 1, PreR, k + 1, inR);
	return root;
}

#endif // BINARY_TREE


