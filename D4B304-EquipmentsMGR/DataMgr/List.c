#include "..\Main.h"
#include "List.h"

Node* MakeNode(Equip* equip)
{
	Node* node = (Node*)malloc(sizeof(Node));
	assert(node);
	node->pEquip = equip;
	node->next = NULL;
	return node;
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

void ListForAllNode(LinkList* list, NodeCallBack pfCallBack, void* pData)
{
	Node* curr = list->head;
	while (curr)
	{
		if (pfCallBack(curr, pData))
			break;
		curr = curr->next;
	}
}