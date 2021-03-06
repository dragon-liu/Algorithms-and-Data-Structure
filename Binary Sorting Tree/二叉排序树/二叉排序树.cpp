// 二叉排序树.cpp: 定义控制台应用程序的入口点。

#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
typedef struct node {
	int data;
	struct node* lchild, *rchild;
}Node;


void InsertElement(int D, Node*&T);  //将结点D插入二叉树
void LDR(Node*root);  //中序遍历输出排序结果
int maxDepth(Node* root);  //输出深度
void Delete(Node*root); //销毁二叉排序树

int main()
{
	Node*root=NULL;  //根节点
	int num;
	int temp;
	printf("请输入要创建的二叉排序树的节点个数:");
	scanf_s("%d", &num);
	printf("请输入相应的节点值:");
	for (int i = 0; i < num; i++) //构造二叉排序树
	{
		scanf_s("%d", &temp);
		InsertElement(temp, root);
	}
	printf("\n二叉排序树的深度为%d\n", maxDepth(root));  //输出深度
	LDR(root);  //输出排序结果
	printf("\n");
	Delete(root);
	system("pause");
    return 0;
}

void InsertElement(int D, Node*&T)  //将结点D插入二叉树
{
	if (T == NULL)
	{
		T = (Node*)malloc(sizeof(Node));
		if (!T)
		{
			printf("内存不够!\n");
			exit(0);
		}
		T->data = D;
		T->lchild = NULL;
		T->rchild = NULL;
	}
	else
	{
		if (D < T->data)
		{
			InsertElement(D, T->lchild);
		}
		else
		{
			InsertElement(D, T->rchild);
		}
	}
}

void LDR(Node*root)  //中序遍历输出排序结果
{
	if (root != NULL)
	{
		LDR(root->lchild);
		printf("%d ", root->data);
		LDR(root->rchild);
	}
}

int maxDepth(Node* root)  //输出深度
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		//递归计算左右子树的深度
		int lDepth = maxDepth(root->lchild);
		int rDepth = maxDepth(root->rchild);

		//使用较大的深度+1
		if (lDepth > rDepth)
		{
			return (lDepth + 1);
		}
		else
		{
			return (rDepth + 1);
		}
	}
}

void Delete(Node*root) //销毁二叉排序树
{
	if (root != NULL)
	{
		Delete(root->lchild);
		Delete(root->rchild);
		free(root);
	}
}
