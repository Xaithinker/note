/*
 * 主程序main()
 * @DATE: 1-24
 * @AUTRHOR: Xu
 * using VStudio
 */
#include "pch.h"
#include "binarytree.h"

const int maxn = 50;
int pre[maxn], in[maxn], post[maxn];

using namespace std;

int main()
{
	int n;
	cout << "输入结点数:" << endl;
	cin >> n;
	cout << "输入先序序列:" << endl;
	for (int i = 0; i < n; i++)
		cin >> pre[i];
	cout << "输入中序序列:" << endl;
	for (int i = 0; i < n; i++)
		cin >> in[i];
	node* root = createbt(0, n - 1, 0, n - 1);
	layer_order(root);
	system("pause");
	return 0;
}