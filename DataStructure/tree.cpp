#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using namespace std;
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};
void PreOrder(TreeNode *T)//前序遍历
{
	if (!T)
		return;
	if (T)
	{
		cout << T->val<<endl;
		PreOrder(T->left);
		PreOrder(T->right);
	}
	
}
void PreOrder(TreeNode *T)//非递归，前序遍历
{
	if (T == NULL)
	{
		return;
	}
	stack<TreeNode*>s;
	s.push(T);
	TreeNode *temp;
	while (!s.empty())
	{
		temp = s.top();
		cout << temp->val;
		s.pop();
		if (temp->left)
		{
			s.push(temp->left);
		}
		if (temp->right)
		{
			s.push(temp->right);
		}
	}
}
 
void InOrder(TreeNode *T)//中序遍历
{
	if (!T)
		return;
	InOrder(T->left);
	cout << T->val;
	InOrder(T->right);
}
 
void PostOrder(TreeNode *T)//后序遍历
{
	if (!T)
		return;
	PostOrder(T->left);
	PostOrder(T->right);
	cout << T->val;
}
void Levelorder(TreeNode *T)//层析遍历
{
	if (!T)
		return;
	TreeNode *temp;
	queue<TreeNode*>q;
	q.push(T);
	while (!q.empty())
	{
		temp = q.front();
		cout << temp->val;
		if (temp->left)
			q.push(temp->left);
		if (temp->right)
			q.push(temp->right);
		q.pop();
	}
}
void DeepOrder(TreeNode *T)//深度遍历
{
	if (!T)
		return;
	TreeNode *temp;
	stack<TreeNode*>s;
	s.push(T);
	while (!s.empty())
	{
		temp = s.top();
		cout << temp->val;
		s.pop();
		if (temp->left)
			s.push(temp->left);
		if (temp->right)
			s.push(temp->right);
	}
}