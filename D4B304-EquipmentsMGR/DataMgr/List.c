#include "..\Main.h"
#include "List.h"

Node* MakeNode(Equip* equip)
{
	Node* node = (Node*)calloc(sizeof(Node));
	assert(node);
	node->pEquip = equip;
	node->next = NULL;
	return node;
}

void FreeNode(Node* node)
{
	FreeEquip(node->pEquip);
	free(node);
	node = NULL;
}

LinkList* MakeList(Node* head, Node* tail)
{
	LinkList* list = (LinkList*)calloc(1, sizeof(LinkList));
	assert(list);
	if (!(list->head = head))	return;
	list->head->next = tail;
	list->LinkNum++;
	if ((list->tail = tail) != list->head)
		list->LinkNum++;
}

void PushFront(LinkList* list, Node* node)
{
	node->next = list->head;
	list->head = node;
	//list->LinkNum++;
}

void PushBack(LinkList* list, Node* node)
{
	list->tail->next = node;
	list->tail = node;
	//list->LinkNum++;
}

void FreeList(LinkList* list)
{
	Node* curr = list->head, * next;
	while (curr)
	{
		next = curr->next;
		FreeNode(curr);
		list->LinkNum--;
		curr = next;
	}
	list->head = list->tail = NULL;
}

void ListForAllNode(LinkList* list, NodeCallBack pfCallBack, void* pData)
{
	Node* curr = list->head;
	while (curr)
	{
		if (!pfCallBack(curr, pData))
			break;
		curr = curr->next;
	}
}

Equip** ListValToArry(LinkList* list)
{
	Equip** equipArry = (Equip**)malloc(sizeof(Equip*) * list->LinkNum);
	assert(equipArry);
	Node* curr = list->head;
	for (int i = 0; i < list->LinkNum; ++i)
	{
		equipArry[i] = curr->pEquip;
		curr = curr->next;
	}
	return equipArry;
}