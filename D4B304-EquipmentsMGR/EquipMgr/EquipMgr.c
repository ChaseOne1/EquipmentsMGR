#include "..\Main.h"
#include "EquipMgr.h"

static Node* ID_Search(LinkList* list, char* id)
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

void AddEquip(LinkList* list, Equip* equip)
{
	Node* node = ID_Search(list, equip->id);
	if (node)
	{
		free(node->pEquip->name);
		free(node->pEquip->id);
		free(node->pEquip);
		node->pEquip = equip;
	}
	else
	{
		Node* newNode = MakeNode(equip);
		//头插
		if (strcmp(equip->id, list->head->pEquip->id) < 0)
		{
			newNode->next = list->head;
			list->head = newNode;
			//写入文件，行数0
		}
		else
		{
			Node* curr = list->head;
			int countLine = 1;
			while (curr && curr->next)
			{
				if (strcmp(equip->id, curr->next->pEquip->id) < 0)//添加
				{
					newNode->next = curr->next;
					curr->next = newNode;
					//写入文件，行数countLine
					return;
				}
				curr = curr->next;
				countLine++;
			}
			//尾插
			if (!curr->next)
				curr->next = newNode;
		}
		list->LinkNum++;
	}
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

void Date_sort(Equip* equip[])
{
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

bool IsScarp(Equip* equip)
{
	return equip->flag;
}

LinkList SearchByName(LinkList* list,char* name)
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