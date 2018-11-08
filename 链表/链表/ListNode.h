#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int DataType;
typedef struct ListNode{
	DataType data;
	struct ListNode *next;
}ListNode;

//��ʼ��
void ListNodeInit(ListNode **ppFirst)
{
	assert(ppFirst != NULL);
	*ppFirst = NULL;
}

//����
void ListNodeDestroy(ListNode **ppFirst)
{
	*ppFirst = NULL;
}

//�����½ڵ�
static ListNode *CreateNode(DataType data)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//ͷ��
void ListNodePushFront(ListNode **ppFirst, DataType data)
{
	ListNode *newNode = CreateNode(data);
	assert(ppFirst != NULL);
	//���������Ϊ������
	if(*ppFirst == NULL)
	{
		*ppFirst = newNode;
		return;
	}
	//�������
	newNode->next = *ppFirst;
	*ppFirst = newNode;
}

//β��
void ListNodePushBack(ListNode **ppFirst, DataType data)
{
	ListNode *cur ;
	ListNode *newNode = CreateNode(data);
	assert(ppFirst != NULL);
	//���������Ϊ������
	if(*ppFirst == NULL)
	{
		*ppFirst = newNode;
		return;
	}
	//�������
	//1.�ҵ����һ������Ҫ������������
	cur = *ppFirst;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	//2.����
	cur->next = newNode;
}

//ͷɾ
void ListNodePopFront(ListNode **ppFirst)
{
	ListNode *del = *ppFirst;
	assert(ppFirst != NULL);
	//assert(*ppFirst != NULL);
	*ppFirst = del->next;
	free(del);
}

//βɾ
void ListNodePopBack(ListNode **ppFirst)
{
	ListNode *del;//������һ��
	ListNode *cur = *ppFirst;
	assert(ppFirst != NULL);
	assert(*ppFirst != NULL);
	//������ֻ��һ���ڵ�
	if((*ppFirst)->next == NULL) 
	{
		free(*ppFirst);
		*ppFirst = NULL;
		return;
	}
	//�������
	//1.�ҵ������ڶ����ڵ�
	
	while(cur->next->next != NULL)
	{
		cur = cur->next;
	}
	//2.�ɴ��ҳ�������һ���ڵ㲢ɾ��
	del = cur->next;
	cur->next = NULL;//һ��Ҫ���ÿգ���ɾ��
	free(del);
}

//��ѯ
ListNode* ListNodeSelect(ListNode *first, DataType data)
{
	ListNode *cur = first;
	while(cur != NULL){
	if(data == cur->data){
		return cur;
	}
	cur = cur->next;
	}
}

//�ڽڵ�ǰ������
ListNode * ListNodeInsert(ListNode **ppFirst, ListNode *pos, DataType data)
{
	ListNode *cur = *ppFirst;
	ListNode *newNode = CreateNode(data);//һ��Ҫ�����¿ռ�
	//ֻ��һ���ڵ��ͷ��
	if(*ppFirst == pos){
		ListNodePushFront(ppFirst,data);
		return;
	}
	//�������
	//1.�ҵ�pos��ǰһ���ڵ�2.����
	while(cur->next != pos){
		cur = cur->next;
	}
	newNode->next = cur->next;
	cur->next = newNode;
}

//ɾ��ָ���ڵ�
void ListNodeErase(ListNode **ppFirst, ListNode *pos)
{
	ListNode *cur = *ppFirst;
	//��Ҫɾ���Ľڵ��ڵ�һ��,ͷɾ
	if(*ppFirst == pos)
	{
		ListNodePopFront(ppFirst);
		return;
	}
	//ͨ�������1.���ҵ�pos��ǰһ���ڵ�2.�ͷ�pos
	while(pos != cur->next)
	{
		cur = cur->next;
	}
	cur->next = pos->next;
	free(pos);
}

void Print(ListNode *first)
{
	ListNode *ret = first;
	for(ret; ret != NULL; ret=ret->next)
	{
		printf("%d -> ",ret->data);
	}
	printf("NULL");
	printf("\n");
}

void Test()
{

	ListNode *result;
	ListNode *first;
	ListNodeInit(&first);

	ListNodePushFront(&first,5);
	ListNodePushFront(&first,4);
	ListNodePushFront(&first,2);
	ListNodePushFront(&first,1);

	result = ListNodeSelect(first,4);

	ListNodeInsert(&first,result,3);
	Print(first);

	ListNodeErase(&first,result);
	Print(first);
}


