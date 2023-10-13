#include "bt.h"
node* MakeBTreeNode(void)
{
	//make binary tree node
	node * nd = new node;
	//initialize 왼쪽 오른쪽 자식 NULL	
	nd->left = NULL;
	nd->right = NULL;
	//return pointer
	return nd;
}
void DeleteBTreeNode(node* bt) {
	delete bt;
}
int GetData(node* bt) {
	return bt->data;
}
void SetData(node* bt, int data) {
	bt->data = data;
}

node* GetLeftSubTree(node* nd)
{
	return nd->left;
}

node* GetRightSubTree(node* nd)
{
	return nd->right;
}

void MakeLeftSubTree(node* main, node* sub) {
	// if there is a node in left link, delete it
	if (main->left != NULL) delete main->left;
	// put sub in left link of main
	main->left = sub;

}
void MakeRightSubTree(node* main, node* sub) {
	// if there is a node in right link, delete it
	if (main->right != NULL) delete main->right;
	// put sub in right link of main
	main->right = sub;
}

void PreorderTraverse(node* bt) // 
{
	// 종료조건
	if (bt == NULL) return;
	// 방문한 노드 출력	
	cout << bt->data;
	// 왼쪽 자식 방문
	PreorderTraverse(bt->left);
	// 오른쪽 자식 방문 
	PreorderTraverse(bt->right);
}

void InorderTraverse(node* bt)
{
	// 종료조건
	if (bt == NULL) return;
	// 방문한 노드 출력	
	InorderTraverse(bt->left);
	cout << bt->data;
	InorderTraverse(bt->right);
}

void PostorderTraverse(node* bt)
{
	// 종료조건
	if (bt == NULL) return;
	PostorderTraverse(bt->left);
	PostorderTraverse(bt->right);
	cout << bt->data;
}




