#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct ComplexListNode{
	int data;
	struct ComplexListNode* random;
	struct ComplexListNode* next;
}ComplexListNode;

static ComplexListNode* ComplexCreateNode(int data)
{
	ComplexListNode *node = (ComplexListNode*)malloc(sizeof(ComplexListNode));
	node->data = data;
	node->next = NULL;
	node->random = NULL;
	return node;
}

ComplexListNode* Copy(ComplexListNode *list)
{
	ComplexListNode* cur = list;
	ComplexListNode* newNode;
	ComplexListNode* result;
	ComplexListNode* node;
	//1.复制节点
	while(cur != NULL)
	{
		newNode = ComplexCreateNode(cur->data);
		newNode->next = cur->next;
		cur->next = newNode;
		cur = cur->next->next;
	}
	//2.复制random
	cur = list;
	while(cur != NULL)
	{
		if(cur->random != NULL)
		{
		cur->next->random = cur->random->next;
		}
		cur = cur->next->next;
	}
	//3.拆分
	cur = list;
	result = list->next;
	while(cur != NULL)
	{
		node = cur->next;
		cur->next = node->next;
		if(cur->next != NULL)
		{
		node->next = cur->next->next;
		}
		else
		{
			node->next = NULL;
		}
		cur = cur->next;
	}
	return result;
}

void PrintComplex(ComplexListNode *list)
{
	ComplexListNode *cur = list;
	for(cur=list; cur!=NULL; cur=cur->next)
	{
		printf("[%d, random(%p)->%d ",cur->data,cur->random,cur->random?cur->random->data:0);
	}
	printf("\n");
}

void Complex()
{
	ComplexListNode *newList;

	ComplexListNode *n1 = ComplexCreateNode(1);
	ComplexListNode *n2 = ComplexCreateNode(2);
	ComplexListNode *n3 = ComplexCreateNode(3);
	ComplexListNode *n4 = ComplexCreateNode(4);

	n1->next = n2;
	n2->next = n3;
	n3->next = n4;

	n1->random = n4;
	n2->random = n2;
	n3->random = n2;

	newList = Copy(n1);
	PrintComplex(n1);
	PrintComplex(newList);
}