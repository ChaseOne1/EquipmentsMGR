#include "..\Main.h"
#include "EquipMgr.h"
#include "..\DataMgr\FileMgr.h"

Node* SearchById(LinkList* list, const char* id)
{
	Node* curr = list->head;
	while (curr)
	{
		if (!strcmp(curr->pEquip->id, id))
			return curr;
		curr = curr->next;
	}
	return NULL;
}

long long GetEquipNo(LinkList* list, const char* id)
{
	long long No = 0;
	Node* curr = list->head;
	while (curr)
	{
		++No;
		if (!strcmp(curr->pEquip->id, id))
			return No;
		curr = curr->next;
	}
	return 0;
}

bool AddEquip(LinkList* list, const Equip* equip)
{
	const bool UPDATE = 0, INSERT = 1;
	if (!list->LinkNum)
	{
		PushFront(list, MakeNode(equip));
		list->tail = list->head;
		list->LinkNum++;
		return INSERT;
	}

	Node* node = SearchById(list, equip->id);
	if (node)
	{
		free(node->pEquip->name);
		free(node->pEquip->id);
		free(node->pEquip);
		node->pEquip = equip;
		return UPDATE;
	}
	else
	{
		Node* newNode = MakeNode(equip), * curr = list->head;
		if (strcmp(equip->id, list->head->pEquip->id) < 0)
			PushFront(list, newNode);
		else
		{
			while (curr->next)
			{
				if (strcmp(equip->id, curr->next->pEquip->id) < 0)
				{
					newNode->next = curr->next;
					curr->next = newNode;
					break;
				}
				curr = curr->next;
			}
			if (!curr->next)
				PushBack(list, newNode);
		}
		list->LinkNum++;
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

static void ID_sort(Equip* equip[])
{

}

void Date_sort(LinkList* list)
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
	//Output
	for (int i = 0; i < list->LinkNum; ++i)
		AppendInfo(&dateList[i], outputFile);

	free(dateList);
}

void ScarpEquip(LinkList* list)
{
	//struct tm t;
	//time_t now;
	//time(&now);
	//localtime_s(&t, &now);
	//long long a, x, y, z, sum;
	//x = t.tm_year + 1900;
	//y = t.tm_mon + 1;
	//z = t.tm_mday;
	//sum = 10000 * x + y * 100 + z;//将当前日期转化为与scrap_date相同格式
	//Node* sky = list->head;
	//while (sky)
	//{
	//	a = sky->pEquip->scrap_date;
	//	if (a < sum)
	//		sky->pEquip->flag = false;
	//	else
	//		sky->pEquip->flag = true;
	//	sky = sky->next;//报废处理
	//}
}

bool IsScarp(const Equip* equip)
{
	return equip->flag;
}

LinkList SearchByName(LinkList* list, const char* name)
{
	LinkList resList;
	resList.head = MakeNode(NULL);
	resList.tail = resList.head;
	resList.LinkNum = 1;
	//结果链表中头节点数据部分为空，第二节点为实首节点,实节点个数为LinkNum-1
	Node* curr = list->head;
	while (curr)
	{
		if (!strcmp(name, curr->pEquip->name))
		{
			resList.tail = resList.tail->next = MakeNode(curr->pEquip);
			resList.LinkNum++;
		}
		curr = curr->next;
	}
	return resList;
}