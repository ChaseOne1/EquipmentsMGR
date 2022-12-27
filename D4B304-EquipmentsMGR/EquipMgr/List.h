#pragma once

typedef struct ListNode
{
	Equip* pEquip;
	struct ListNode* next;
}Node;

typedef struct NodeList
{
	Node* head;
	Node* tail;
	int LinkNum;
}LinkList;

Node* MakeNode(Equip* equip);

void List_PushBack(LinkList* list, Node* node);//和插入的区别在于更新头尾节点

void List_PushFront(LinkList* list, Node* node);

void List_PopBack(LinkList* list);//注意更改实际链表

void List_PopFront(LinkList* list);

void List_Insert(LinkList* list, Node* node);//有序插入

//void List_Delete(LinkList* list,Equip* equip);

void List_SetValue(Node* link);

Node* PriorLink(LinkList* list);

Node* NextLink(LinkList* list);

Node* FindLink(LinkList* list, char name[]);