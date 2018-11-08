#pragma once

#include "ListNode.h"

//从尾到头打印单链表
void PrintReverse(ListNode *first)
{
	//第一种方法
	//ListNode *cur ;//标记要打印的节点
	//ListNode *end = NULL;//要打印的后一个节点
	//while(end != first)
	//{
	//	cur = first;
	//	while(cur->next != end)
	//	{
	//		cur = cur->next;
	//	}
	//	printf("%d ",cur->data);
	//	end = cur;
	//第二种方法：递归
	if( first == NULL)
	{
		return;
	}
		PrintReverse(first->next);
	printf("%d ",first->data);
}
void PrintReverse(ListNode* first)
{
	ListNode* end = NULL;
	ListNode* cur;
	while(end != first)
	{
		cur = first;
		while(cur->next != end)
		{
			cur = cur->next;
		}
		printf("%d ",cur->data);
		end = cur;
	}
}

void PrintReverseD()
{
	ListNode *first;
	ListNodeInit(&first);

	ListNodePushFront(&first,5);
	ListNodePushFront(&first,4);
	ListNodePushFront(&first,3);
	ListNodePushFront(&first,2);
	ListNodePushFront(&first,1);

	Print(first);

	PrintReverse(first);
}

//逆置/反转单链表
ListNode *ReverseList(ListNode *first)
{
	//方法一：重新创建一个链表
	ListNode *result = NULL;
	ListNode *cur = first;
	ListNode *node;//中间存放的节点
	//头删，头插，开辟第三个节点
	while(cur != NULL)
	{
		//头删（节点只是被摘下，并没有真正删除）
		node = cur;
		cur = cur->next;
		//插入
		node->next = result;
		result = node;
	}
	return result;
	//方法二：不需要重新创建链表
	/*ListNode *p1 = NULL;
	ListNode *p2 = first;
	ListNode *p3 = first->next;
	while(p2 != NULL){
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		if(p3 != NULL)
		{
			p3 = p3->next;
		}
	}
	return p1;*/
}

ListNode *ReverseList(ListNode *first)
{
	/*
	ListNode* p1 = NULL;
	ListNode* p2 = first;
	ListNode* p3 = first->next;
	while(p2 != NULL){
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		if(p3 != NULL)
		{
			p3 = p3->next;
		}
	}
	return p1;*/
	ListNode* result = NULL;
	ListNode* cur = first;
	ListNode* node;
	while(cur != NULL){
	node = cur;
	cur = cur->next;
	node->next = result;
	result = node;
	}
	return result;
}

void ReverseListD()
{
	ListNode *ret;
	ListNode *first;
	ListNodeInit(&first);

	ListNodePushFront(&first,5);
	ListNodePushFront(&first,4);
	ListNodePushFront(&first,3);
	ListNodePushFront(&first,2);
	ListNodePushFront(&first,1);

	Print(first);

	ret = ReverseList(first);
	Print(ret);
}

//删除一个无头单链表的非尾节点
void RemoveNoFirst(ListNode *pos)
{
	ListNode *del = pos->next;
	pos->data = pos->next->data;
	pos->next = pos->next->next;
	free(del);
}

//无头链表的插入(在pos后插入一个节点)
void InsertNoHead(ListNode* pos, DataType data)
{
	ListNode* newNode = CreateNode(data);
	ListNode* cur;
	DataType tmp;
	cur = pos;
	newNode->next = cur->next;
	cur->next = newNode;
	tmp = cur->data;
	cur->data = newNode->data;
	newNode->data = tmp;
}


//约瑟夫环
ListNode * JosephCircle(ListNode *first, int k)
{
	ListNode *end = first;//找最后一个节点
	ListNode *cur = first;
	ListNode *before = NULL;
	int i = 0;
	//1.链表构成一个环
	while(end->next != NULL)
	{
		end = end->next;
	}
	end->next = first;
	//2.剩余个数>1,前进k步
	while(cur->next != cur)//一定是不等于自己
	{
		for(i=0; i<k-1; i++)//找到cur的前一个节点,cur是要删除的节点
		{
			before = cur;
			cur = cur->next;
		}
		before->next = cur->next;
		free(cur);
		//循环继续
		cur = before->next;
	}
	cur->next = NULL;
	return cur;
}

void JosephCircle1()
{
	ListNode *first = NULL;
	ListNode *suv;
	int i = 0;
	for(i=1; i<7; i++)
	{
		ListNodePushBack(&first,i);
	}
	suv = JosephCircle(first,3);
	printf("%d\n",suv->data);
}

//合并两个有序链表，合并后依然有序（升序）
ListNode * MergeOrderedList(ListNode *list1, ListNode *list2)
{
	ListNode *cur1 = list1;
	ListNode *cur2 = list2;
	ListNode *result = NULL;//合并后的链表
	ListNode *tail = NULL;//记录新链表的最后一个节点
	ListNode *next;//遍历过程中的下一个节点
	while(cur1!=NULL && cur2!=NULL)
	{
		if(cur1->data <= cur2->data)
		{
			if(result != NULL)//新链表不为空，在最后一个节点做插入
			{
				next = cur1->next;
				tail->next = cur1;
				cur1->next = NULL;//最后一个节点的next置为空，防止链表悬空
				tail = cur1;
				cur1 = next;
			}
			else{
				next = cur1->next;
				result = cur1;
				cur1->next = NULL;
				tail = cur1;
				cur1 = next;
			}
		}
		else{
			if(result != NULL)//新链表不为空，在最后一个节点做插入
			{
				next = cur2->next;
				tail->next = cur2;
				cur2->next = NULL;//最后一个节点的next置为空，防止链表悬空
				tail = cur2;
				cur2 = next;
			}
			else{
				next = cur2->next;
				result = cur2;
				cur2->next = NULL;
				tail = cur2;
				cur2 = next;
			}
		}
	}
	if(cur1 == NULL)
	{
		tail->next = cur2;
	}
	if(cur2 == NULL)
	{
		tail->next = cur1;
	}
	return result;
}

void MergeOrderedList1()
{
	ListNode *result;
	ListNode *list1 = NULL;
	ListNode *list2 = NULL;
	ListNodePushBack(&list1,1);
	ListNodePushBack(&list1,1);
	ListNodePushBack(&list1,3);
	ListNodePushBack(&list1,4);
	ListNodePushBack(&list1,5);

	ListNodePushBack(&list2,1);
	ListNodePushBack(&list2,2);
	ListNodePushBack(&list2,4);

	result = MergeOrderedList(list1, list2);

	Print(result);
}

//求两个已排序单链表中相同的数据(相同数据只出现一次)
void PrintIntersection(ListNode *list1,ListNode *list2)
{
	ListNode *cur1 = list1;
	ListNode *cur2 = list2;
	DataType data;
	while(cur1!=NULL && cur2!=NULL)
	{
		if(cur1->data == cur2->data)
		{
			printf("%d ",cur1->data);
			data = cur1->data;
			while(cur1!=NULL && cur1->data==data)
			{
			cur1 = cur1->next;
			}
			while(cur2!=NULL && cur2->data==data)
			{
			cur2 = cur2->next;
			}
		}
		else if(cur1->data < cur2->data)
		{
			cur1 = cur1->next;
		}
		else
		{
			cur2 = cur2->next;
		}
	}
}

void PrintIntersection1()
{
	ListNode *list1 = NULL;
	ListNode *list2 = NULL;
	ListNodePushBack(&list1,1);
	ListNodePushBack(&list1,1);
	ListNodePushBack(&list1,3);
	ListNodePushBack(&list1,4);
	ListNodePushBack(&list1,5);

	ListNodePushBack(&list2,1);
	ListNodePushBack(&list2,2);
	ListNodePushBack(&list2,4);

	PrintIntersection(list1, list2);
}

//查找单链表的中间节点（只能遍历一次）
void FindMid(ListNode *first)
{
	ListNode *fast = first;
	ListNode *slow = first;
	while(1)
	{
		fast = fast->next;
		if(fast == NULL)
		{
			break;
		}
		fast = fast->next;
		if(fast == NULL)
		{
			break;
		}
		slow = slow->next;
	}
	printf("%d\n",slow->data);
}

void FindMid1()
{
	ListNode *first = NULL;

	ListNodePushFront(&first,5);
	ListNodePushFront(&first,4);
	ListNodePushFront(&first,3);
	ListNodePushFront(&first,2);
	ListNodePushFront(&first,1);

	FindMid(first);

	ListNodePushBack(&first,6);

	FindMid(first);
}

//查找单链表的倒数第K个节点（只能遍历一次）
void FindTailk(ListNode *first,int k)
{
	ListNode *forword = first;
	ListNode *backword = first;
	while(k--)
	{
		forword = forword->next;
	}
	while(forword != NULL)
	{
		forword = forword->next;
		backword = backword->next;
	}
	printf("%d\n",backword->data);
}

void FindTailk1()
{
	ListNode *first = NULL;

	ListNodePushFront(&first,5);
	ListNodePushFront(&first,4);
	ListNodePushFront(&first,3);
	ListNodePushFront(&first,2);
	ListNodePushFront(&first,1);

	FindTailk(first,2);
}

//删除链表倒数第K个节点
void PopTailk(ListNode **ppFirst, int k)
{
	ListNode *forword = *ppFirst;
	ListNode *backword = *ppFirst;
	ListNode *cur = *ppFirst;//标记要删除节点的前一个
	while(k--)
	{
		forword = forword->next;
	}
	while(forword != NULL)
	{
		forword = forword->next;
		cur = backword;
		backword = backword->next;
	}
	cur->next = backword->next;
	free(backword);
}

void PopTailk1()
{
	ListNode *first = NULL;

	ListNodePushFront(&first,5);
	ListNodePushFront(&first,4);
	ListNodePushFront(&first,3);
	ListNodePushFront(&first,2);
	ListNodePushFront(&first,1);

	PopTailk(&first,2);

	Print(first);
}

