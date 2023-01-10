#include "..\Main.h"
#include "EquipMgr.h"
#include "..\DataMgr\FileMgr.h"


bool AddEquip(LinkList* list, const Equip* equip)
{
	const bool UPDATE = 0, INSERT = 1;
	Node* node = SearchById(list, equip->id);
	if (node)
	{
		FreeEquip(&node->pEquip);
		node->pEquip = equip;
		return UPDATE;
	}
	else
	{
		Node* newNode = MakeNode(equip), * curr = list->head;
		if (!list->LinkNum)
			PushFront(list, MakeNode(equip));
		else if (strcmp(equip->id, list->head->pEquip->id) < 0)
			PushFront(list, newNode);
		else
		{
			while (curr->next)
			{
				if (strcmp(equip->id, curr->next->pEquip->id) < 0)
				{
					newNode->next = curr->next;
					curr->next = newNode;
					list->LinkNum++;
					break;
				}
				curr = curr->next;
			}
			if (!curr->next)
				PushBack(list, newNode);
		}
	}
	return INSERT;
}

unsigned char* TypeCount(LinkList* list)
{
	unsigned char* TYPE = (unsigned char*)calloc(TOTAL * 2 + 2, sizeof(unsigned char));
	assert(TYPE);
	Node* curr = list->head;
	while (curr)
	{
		switch (curr->pEquip->type)
		{
		case MEC:	++TYPE[MEC];
			if (curr->pEquip->flag) ++TYPE[MEC + TOTAL + 1];	break;
		case CHM:	++TYPE[CHM];
			if (curr->pEquip->flag) ++TYPE[CHM + TOTAL + 1];	break;
		case MDC:	++TYPE[MDC];
			if (curr->pEquip->flag) ++TYPE[MDC + TOTAL + 1];	break;
		case ELC:	++TYPE[ELC];
			if (curr->pEquip->flag) ++TYPE[ELC + TOTAL + 1];	break;
		case SPC:	++TYPE[SPC];
			if (curr->pEquip->flag) ++TYPE[SPC + TOTAL + 1];	break;
		default:	break;
		}
		curr = curr->next;
	}
	for (int i = 0; i < TOTAL; ++i)
	{
		TYPE[TOTAL] += TYPE[i];
		TYPE[TOTAL + TOTAL + 1] += TYPE[TOTAL + i + 1];
	}
	return TYPE;
}

Equip** Date_sort(LinkList* list)
{
	Equip** dateList = ListValToArry(list);
	//Sort
	for (int i = 0; i < list->LinkNum - 1; ++i)
	{
		int end = i;
		Equip* key = dateList[end + 1];
		while (end >= 0 && dateList[end]->buy_date > key->buy_date)
		{
			dateList[end + 1] = dateList[end];
			--end;
		}
		dateList[end + 1] = key;
	}
	return dateList;
}

void ScarpEquip(Equip* equip,long long scrap_date)
{
	equip->flag = equip->scrap_date = scrap_date;
}

Node* SearchById(LinkList* list, const char* id)
{
	if (!list->LinkNum)	return NULL;
	Node* curr = list->head;
	while (curr)
	{
		if (!strcmp(curr->pEquip->id, id))
			return curr;
		curr = curr->next;
	}
	return NULL;
}

Node* Name_cmp(Node* node, void* pData)
{
	if (!strcmp((char*)pData, node->pEquip->name))
		return node;
	else
		return NULL;
}

Node* IsScarpped_cmp(Node* node, void* pData)
{
	if (node->pEquip->flag == (bool)pData)
		return node;
	else
		return NULL;
}