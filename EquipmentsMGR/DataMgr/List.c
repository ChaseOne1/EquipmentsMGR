#include "..\Main.h"

Node* MakeNode(Equip* equip)
{
	Node* node = (Node*)malloc(sizeof(Node));
	assert(node);
	node->pEquip = equip;
	node->next = NULL;
	return node;
}

void FreeNode(LinkList* list, Node** pNode, bool flag)
{
	Node* node = *pNode;
	if (node == NULL)
		return;
	if (list)
	{
		if (node == list->head)
		{
			PopFront(list, flag);
			return;
		}
		else if (node == list->tail)
		{
			PopBack(list, flag);
			return;
		}
		else
		{
			Node* curr = list->head;
			while (curr)
			{
				if (curr->next == node)
				{
					curr->next = node->next;
					break;
				}
				curr = curr->next;
			}
		}
		list->LinkNum--;
	}
	if (flag)	FreeEquip(&node->pEquip);
	free(node);
	node = NULL;
	*pNode = NULL;
}

LinkList* MakeList(Node* head, Node* tail)
{
	LinkList* list = (LinkList*)calloc(1, sizeof(LinkList));
	assert(list);
	if (!(list->head = head))	return list;
	list->head->next = tail;
	list->LinkNum++;
	if (tail && (list->tail = tail) != list->head)
		list->LinkNum++;
	return list;
}

void FreeList(LinkList** pList, bool flag)
{
	LinkList* list = *pList;
	if (list == NULL)
		return;
	Node* curr = list->head, * next;
	while (curr)
	{
		next = curr->next;
		FreeNode(NULL, &curr, flag);
		list->LinkNum--;
		curr = next;
	}
	list->head = list->tail = NULL;
	list = NULL;
	*pList = NULL;
}

void PushFront(LinkList* list, Node* node)
{
	if (list == NULL)
		return;
	if (!list->LinkNum)
		list->head = list->tail = node;
	else
		node->next = list->head;
	list->head = node;
	list->LinkNum++;
}

void PopFront(LinkList* list, bool flag)
{
	if (!list || !list->LinkNum)
		return;
	Node* next = list->head->next;
	FreeNode(NULL, &list->head, false);
	list->head = next;
	list->LinkNum--;
}

void PushBack(LinkList* list, Node* node)
{
	if (list == NULL)
		return;
	if (!list->LinkNum)
		list->tail = list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->LinkNum++;
}

void PopBack(LinkList* list, bool flag)
{
	if (!list || !list->LinkNum)
		return;
	Node* curr = list->head;
	while (curr)
	{
		if (curr->next == list->tail)
		{
			list->tail = curr;
			break;
		}
		curr = curr->next;
	}
	FreeEquip(&curr->next->pEquip);
	FreeNode(NULL, &curr->next, false);
	list->LinkNum--;
}

LinkList* ListForAllNodeL(LinkList* list, NodeCallBack pfCallBack, void* pData)
{
	LinkList* newList = MakeList(NULL, NULL);
	Node* curr = list->head, * result = NULL;
	while (curr)
	{
		if (pfCallBack(curr, pData))
			PushBack(newList, MakeNode(curr->pEquip));
		curr = curr->next;
	}
	return newList;
}

void ListForAllNodeV(LinkList* list, NodeCallBack pfCallBack, void* pData)
{
	Node* curr = list->head;
	while (curr)
	{
		if (!pfCallBack(curr, pData))
			break;
		curr = curr->next;
	}
}

Equip** ListValToArray(LinkList* list)
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