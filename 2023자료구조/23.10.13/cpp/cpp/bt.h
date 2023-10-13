#pragma once
#include <iostream>
#include<stack>
using namespace std;

struct node
{
	int data;
	struct node* left;
	struct node* right;
};

node* MakeBTreeNode(void);
void DeleteBTreeNode(node* bt);
int GetData(node* bt);
void SetData(node* bt, int data);
void MakeLeftSubTree(node* main, node* sub);
void MakeRightSubTree(node* main, node* sub);
node* GetLeftSubTree(node* nd);
node* GetRightSubTree(node* nd);
void PreorderTraverse(node* bt);
void InorderTraverse(node* bt);
void PostorderTraverse(node* bt);


class BST {
public:
	node* root = NULL;
	void Insert(node* node);
	void InsertRecur(node* root, node* node);
	void Delete(int key);
	void Delete(node* parent, node* node);
	void SetCursorPosition(int x, int y);
	void Print(node* node, int x, int y);
};