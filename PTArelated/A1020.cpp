/* Tree Traversals （25）
 * Suppose that all the keys in a binary tree are distinct positive integers. 
   Given the postorder and inorder traversal sequences, you are supposed to output the level order traversal sequence of the corresponding binary tree.
 * Input Specification:
   Each input file contains one test case. For each case, the first line gives a positive integer N (≤30), the total number of nodes in the binary tree. 
   The second line gives the postorder sequence and the third line gives the inorder sequence.
   All the numbers in a line are separated by a space.
 * Output Specification:
   For each test case, print in one line the level order traversal sequence of the corresponding binary tree.
   All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.
 * Sample Input:
  7
  2 3 1 5 7 6 4
  1 2 3 4 5 6 7
 * Sample Output:
   4 1 6 3 5 7 2
 * C++ version
 */

#include <iostream>
#include <queue>

using namespace std;

struct node
{
	int data;
	node* lchild;
	node* rchild;
};

//层序遍历
int btBFS(node* &root);
//使用队列创建二叉树
node* createbt(int PostL, int PostR, int inL, int inR);

const int maxlength = 30;
int post[maxlength], in[maxlength];
int n;

int btBFS(node* &root)
{
	int num = 0;
	queue<node*> q;
	q.push(root);
	while (!q.empty())
	{
		node* now = q.front();
		q.pop();
		cout << now->data; num++;
		if (num < n)cout << ' ';
		if (now->lchild != nullptr)q.push(now->lchild);
		if (now->rchild != nullptr)q.push(now->rchild);
	}
	return 0;
}

node* createbt(int PostL, int PostR, int inL, int inR)
{
	if (PostL > PostR)
		return nullptr;
	node* root = new node;
	root->data = post[PostR]; //根结点
	int k = 0;
	for (k = inL; k <= inR; k++) //寻找中序的K值
	{
		if (in[k] == post[PostR])break;
	}
	int numLeft = k - inL; //左子树结点数
	//左子树的后序序列[PostL, PostL + numLeft - 1] 中序序列[inL, k-1]
	root->lchild = createbt(PostL, PostL + numLeft - 1, inL, k - 1);
	//右子树后序序列[PostL + numLeft, PostR-1] 中序序列[k+1, inR]
	root->rchild = createbt(PostL + numLeft, PostR - 1, k + 1, inR);
	return root;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> post[i];
	for (int i = 0; i < n; i++)
		cin >> in[i];
	node* root = createbt(0, n - 1, 0, n - 1);
	btBFS(root);
	return 0;
}
