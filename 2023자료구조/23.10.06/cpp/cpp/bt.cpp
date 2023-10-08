#include "bt.h"

BTreeNode* MakeBTreeNode(void)
{
	//make binary tree
	//initialize
	//return pointer
	BTreeNode* root = new BTreeNode();
	root->left = nullptr;
	root->right = nullptr;

	return root;
}
void DeleteBTreeNode(BTreeNode* bt) {
	delete bt;
}
int GetData(BTreeNode* bt) {
	return bt->data;
}
void SetData(BTreeNode* bt, int data) {
	bt->data = data;
}

void MakeLeftSubTree(BTreeNode* main, BTreeNode* sub) {
	// if there is a node in left link, delete it
	// put sub in left link of main
	if (main->left != nullptr)
		delete main->left;

	main->left = sub;
}
void MakeRightSubTree(BTreeNode* main, BTreeNode* sub) {
	// if there is a node in right link, delete it
	// put sub in right link of main
	if (main->right != nullptr)
		delete main->right;

	main->right = sub;
}
void PreorderTraverse(BTreeNode* bt)
{
	// 구현해보자!
	if (bt == nullptr)
		return;

	std::cout << bt->data << ' ';
	PreorderTraverse(bt->left);
	PreorderTraverse(bt->right);
}
void InorderTraverse(BTreeNode* bt)
{
	// 구현해보자!
	if (bt == nullptr)
		return;
	
	InorderTraverse(bt->left);
	std::cout << bt->data << ' ';
	InorderTraverse(bt->right);
}
void PostorderTraverse(BTreeNode* bt)
{
	// 구현해보자!
	if (bt == nullptr)
		return;

	PostorderTraverse(bt->left);
	PostorderTraverse(bt->right);
	std::cout << bt->data << ' ';
}


