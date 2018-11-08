#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int DataType;
typedef struct ListNode{
	DataType data;
	struct ListNode *next;
}ListNode;

//初始化
void ListNodeInit(ListNode **ppFirst)
{
	assert(ppFirst != NULL);
	*ppFirst = NULL;
}

//销毁
void ListNodeDestroy(ListNode **ppFirst)
{
	*ppFirst = NULL;
}

//创建新节点
static ListNode *CreateNode(DataType data)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
	assert(newNode);
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//头插
void ListNodePushFront(ListNode **ppFirst, DataType data)
{
	ListNode *newNode = CreateNode(data);
	assert(ppFirst != NULL);
	//特殊情况：为空链表
	if(*ppFirst == NULL)
	{
		*ppFirst = newNode;
		return;
	}
	//正常情况
	newNode->next = *ppFirst;
	*ppFirst = newNode;
}

//尾插
void ListNodePushBack(ListNode **ppFirst, DataType data)
{
	ListNode *cur ;
	ListNode *newNode = CreateNode(data);
	assert(ppFirst != NULL);
	//特殊情况：为空链表
	if(*ppFirst == NULL)
	{
		*ppFirst = newNode;
		return;
	}
	//正常情况
	//1.找到最后一个数，要遍历整个链表
	cur = *ppFirst;
	while(cur->next != NULL)
	{
		cur = cur->next;
	}
	//2.插入
	cur->next = newNode;
}

//头删
void ListNodePopFront(ListNode **ppFirst)
{
	ListNode *del = *ppFirst;
	assert(ppFirst != NULL);
	//assert(*ppFirst != NULL);
	*ppFirst = del->next;
	free(del);
}

//尾删
void ListNodePopBack(ListNode **ppFirst)
{
	ListNode *del;//倒数第一个
	ListNode *cur = *ppFirst;
	assert(ppFirst != NULL);
	assert(*ppFirst != NULL);
	//链表中只有一个节点
	if((*ppFirst)->next == NULL) 
	{
		free(*ppFirst);
		*ppFirst = NULL;
		return;
	}
	//正常情况
	//1.找到倒数第二个节点
	
	while(cur->next->next != NULL)
	{
		cur = cur->next;
	}
	//2.由此找出倒数第一个节点并删除
	del = cur->next;
	cur->next = NULL;//一定要先置空，再删除
	free(del);
}

//查询
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

//在节点前做插入
ListNode * ListNodeInsert(ListNode **ppFirst, ListNode *pos, DataType data)
{
	ListNode *cur = *ppFirst;
	ListNode *newNode = CreateNode(data);//一定要申请新空间
	//只有一个节点就头插
	if(*ppFirst == pos){
		ListNodePushFront(ppFirst,data);
		return;
	}
	//正常情况
	//1.找到pos的前一个节点2.插入
	while(cur->next != pos){
		cur = cur->next;
	}
	newNode->next = cur->next;
	cur->next = newNode;
}

//删除指定节点
void ListNodeErase(ListNode **ppFirst, ListNode *pos)
{
	ListNode *cur = *ppFirst;
	//若要删除的节点在第一个,头删
	if(*ppFirst == pos)
	{
		ListNodePopFront(ppFirst);
		return;
	}
	//通常情况：1.先找到pos的前一个节点2.释放pos
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


