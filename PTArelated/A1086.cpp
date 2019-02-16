/* Tree Traversals Again （25 分）
 * An inorder binary tree traversal can be implemented in a non-recursive way with a stack.
   For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). 
   Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. Your task is to give the postorder traversal sequence of this tree.
 * Input Specification:
   Each input file contains one test case. For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N).
   Then 2N lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.
 * Output Specification:
   For each test case, print the postorder traversal sequence of the corresponding tree in one line.
   A solution is guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.
 * Sample Input:
   6
   Push 1
   Push 2
   Push 3
   Pop
   Pop
   Push 4
   Pop
   Pop
   Push 5
   Push 6
   Pop
   Pop
 * Sample Output:
   3 4 2 6 5 1
 * C++ Version:
 */

#include <iostream>
#include <stack>
#include <string>
using namespace std;
struct node
{
	int data;
	node* lchild;
	node* rchild;
};

int n = 0;
const int maxlength = 30;
int pre[maxlength], in[maxlength];
node* create(int PreL, int PreR, int inL, int inR)
{
	if (PreL > PreR)
		return nullptr;
	node* root = new node;
	root->data = pre[PreL];
	int k = 0;
	for (k = inL; k < inR; k++)  //注意！这里是从[inL, inR]遍历，并不一定是0开始
	{
		if (in[k] == pre[PreL])break;
	}
	int numLeft = k - inL;  //中序来区分左右子树
	root->lchild = create(PreL + 1, PreL + numLeft, inL, k - 1);
	root->rchild = create(PreL + numLeft + 1, PreR, k + 1, inR);
	return root;
}

int num = 0;  //global counter
int postorder(node* &root)
{
	if (root == nullptr)
		return 0;
	postorder(root->lchild);
	postorder(root->rchild);
	cout << root->data;
	num++;
	if (num < n){cout << ' ';}
	return 0;
}

int main()
{
	stack<int> st;
	int data = 0;
	int preIndex = 0, inIndex = 0;
	string str;
	cin >> n;
	for (int i = 0; i < 2 * n; i++)
	{
		cin >> str;
		if (str == "Push")
		{
			cin >> data;
			pre[preIndex++] = data;
			st.push(data);
		}
		else  //当push时为先序遍历；当pop时，取栈顶为中序遍历，别忘记pop出。
		{
			in[inIndex++] = st.top();
			st.pop();
		}
	}
	node* root = create(0, n - 1, 0, n - 1);
	postorder(root);
	return 0;
}
