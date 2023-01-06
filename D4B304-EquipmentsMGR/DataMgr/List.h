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

typedef Node* (*NodeCallBack)(Node* node, void* pData);

Node* MakeNode(Equip* equip);

void ListInitialize();

void PushFront(LinkList* list, Node* node);

void PushBack(LinkList* list, Node* node);

void ListForAllNode(LinkList* list, NodeCallBack pfCallBack, void* pData);