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