#pragma once

#include "ListNode.h"

//��β��ͷ��ӡ������
void PrintReverse(ListNode *first)
{
	//��һ�ַ���
	//ListNode *cur ;//���Ҫ��ӡ�Ľڵ�
	//ListNode *end = NULL;//Ҫ��ӡ�ĺ�һ���ڵ�
	//while(end != first)
	//{
	//	cur = first;
	//	while(cur->next != end)
	//	{
	//		cur = cur->next;
	//	}
	//	printf("%d ",cur->data);
	//	end = cur;
	//�ڶ��ַ������ݹ�
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

//����/��ת������
ListNode *ReverseList(ListNode *first)
{
	//����һ�����´���һ������
	ListNode *result = NULL;
	ListNode *cur = first;
	ListNode *node;//�м��ŵĽڵ�
	//ͷɾ��ͷ�壬���ٵ������ڵ�
	while(cur != NULL)
	{
		//ͷɾ���ڵ�ֻ�Ǳ�ժ�£���û������ɾ����
		node = cur;
		cur = cur->next;
		//����
		node->next = result;
		result = node;
	}
	return result;
	//������������Ҫ���´�������
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

//ɾ��һ����ͷ������ķ�β�ڵ�
void RemoveNoFirst(ListNode *pos)
{
	ListNode *del = pos->next;
	pos->data = pos->next->data;
	pos->next = pos->next->next;
	free(del);
}

//��ͷ����Ĳ���(��pos�����һ���ڵ�)
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


//Լɪ��
ListNode * JosephCircle(ListNode *first, int k)
{
	ListNode *end = first;//�����һ���ڵ�
	ListNode *cur = first;
	ListNode *before = NULL;
	int i = 0;
	//1.������һ����
	while(end->next != NULL)
	{
		end = end->next;
	}
	end->next = first;
	//2.ʣ�����>1,ǰ��k��
	while(cur->next != cur)//һ���ǲ������Լ�
	{
		for(i=0; i<k-1; i++)//�ҵ�cur��ǰһ���ڵ�,cur��Ҫɾ���Ľڵ�
		{
			before = cur;
			cur = cur->next;
		}
		before->next = cur->next;
		free(cur);
		//ѭ������
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

//�ϲ��������������ϲ�����Ȼ��������
ListNode * MergeOrderedList(ListNode *list1, ListNode *list2)
{
	ListNode *cur1 = list1;
	ListNode *cur2 = list2;
	ListNode *result = NULL;//�ϲ��������
	ListNode *tail = NULL;//��¼����������һ���ڵ�
	ListNode *next;//���������е���һ���ڵ�
	while(cur1!=NULL && cur2!=NULL)
	{
		if(cur1->data <= cur2->data)
		{
			if(result != NULL)//������Ϊ�գ������һ���ڵ�������
			{
				next = cur1->next;
				tail->next = cur1;
				cur1->next = NULL;//���һ���ڵ��next��Ϊ�գ���ֹ��������
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
			if(result != NULL)//������Ϊ�գ������һ���ڵ�������
			{
				next = cur2->next;
				tail->next = cur2;
				cur2->next = NULL;//���һ���ڵ��next��Ϊ�գ���ֹ��������
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

//��������������������ͬ������(��ͬ����ֻ����һ��)
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

//���ҵ�������м�ڵ㣨ֻ�ܱ���һ�Σ�
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

//���ҵ�����ĵ�����K���ڵ㣨ֻ�ܱ���һ�Σ�
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

//ɾ����������K���ڵ�
void PopTailk(ListNode **ppFirst, int k)
{
	ListNode *forword = *ppFirst;
	ListNode *backword = *ppFirst;
	ListNode *cur = *ppFirst;//���Ҫɾ���ڵ��ǰһ��
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

