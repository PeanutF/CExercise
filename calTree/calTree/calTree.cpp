// calTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "malloc.h"
#include <string>
#include <iostream>

using namespace std;

char formula[20];
int flag = 0;

typedef struct BtreeNode {
	char data;
	struct BtreeNode *lchild;
	struct BtreeNode *rchild;
	struct BtreeNode *parent;
}BtreeNode;

void input() {
	printf("输入表达式\n");
	scanf_s("%s", &formula, 20);
}

BtreeNode* createTree(int s, int e) throw(exception){
	if (s < 0 || e < 0) {
		flag = 1;
		return NULL;
	}
	if (flag == 1)
		return NULL;
	int as = 0, md = 0, flag = 0;
	if (e - s == 1) {
		if (formula[s] == '+' || formula[s] == '-' || formula[s] == '*' || formula[s] == '/')
			flag = 1;
		BtreeNode* b = (BtreeNode*)malloc(sizeof(BtreeNode));
		b->lchild = b->rchild = NULL;
		b->data = formula[s];
		return b;
	}
	for (int i = s; i < e; i++) {
		if (formula[i] == '(')
			flag++;
		else if (formula[i] == ')')
			flag--;
		if (!flag) {
			if (formula[i] == '+' || formula[i] == '-')
				as = i;
			if (formula[i] == '*' || formula[i] == '/')
				md = i;
		}
	}
	if (as == 0 && md == 0)
		return createTree(s + 1, e - 1);
	if (as != 0) {
		BtreeNode* b = (BtreeNode*)malloc(sizeof(BtreeNode));
		b->data = formula[as];
		b->lchild = createTree(s, as);
		b->rchild = createTree(as + 1, e);
		if (b->lchild == NULL || b->rchild == NULL) {
			flag = 1;
			return NULL;
		}
		b->lchild->parent = b;
		b->rchild->parent = b;
		return b;
	}
	else if (md != 0) {
		BtreeNode* b = (BtreeNode*)malloc(sizeof(BtreeNode));
		b->data = formula[md];
		b->lchild = createTree(s, md);
		b->rchild = createTree(md + 1, e);
		if (b->lchild == NULL || b->rchild == NULL) {
			flag = 1;
			return NULL;
		}
		b->lchild->parent = b;
		b->rchild->parent = b;
		return b;
	}
	return NULL;
}

string cal(BtreeNode* b) {
	string result;
	if (b == NULL) return 0;
	switch (b->data) {
	case '+':
		//result = cal(b->lchild) + cal(b->rchild);
		//break;
	case '-':
		if(b->parent != NULL)
		if (b->parent->data == '*' || b->parent->data == '/') {
			result = "(" + cal(b->lchild) + b->data + cal(b->rchild) + ")";
			break;
		}
		//result = cal(b->lchild) - cal(b->rchild);
		//break;
	case '*':
		//result = cal(b->lchild) * cal(b->rchild);
		//break;
	case '/':
		result = cal(b->lchild) + b->data + cal(b->rchild);
		break;
		//result = cal(b->lchild) / cal(b->rchild);
		//break;
	default:result = b->data;
	}
	return result;
}

string calBack(BtreeNode* b) {
	string result;
	if (b == NULL) return 0;
	switch (b->data) {
	case '+':
		//result = cal(b->lchild) + cal(b->rchild);
		//break;
	case '-':
		//result = cal(b->lchild) - cal(b->rchild);
		//break;
	case '*':
		//result = cal(b->lchild) * cal(b->rchild);
		//break;
	case '/':
		result = calBack(b->lchild) + calBack(b->rchild) + b->data;
		break;
		//result = cal(b->lchild) / cal(b->rchild);
		//break;
	default:result = b->data;
	}
	return result;
}

int main()
{
	input();
	int length = 0;
	for (int i = 0; formula[i] != '\0'; i++) {
		length++;
	}
	BtreeNode* tree = NULL;
	try {
		tree = createTree(0, length);
		
	}
	catch (exception e) {
		cout << "error";
		return 0;
	}
	if (flag == 1) {
		cout << "error";
		return 0;
	}	
	//printf("结果为%s", cal(tree));
	tree->parent = NULL;
	string result = cal(tree);
	string resultBack = calBack(tree);
	cout << resultBack + "\n";

	cout << result;
	return 0;
}