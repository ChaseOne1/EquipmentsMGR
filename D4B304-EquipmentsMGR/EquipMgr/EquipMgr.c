#include "..\Main.h"
#include "EquipMgr.h"

void InputInfo()
{
}

void AddEquip(LinkList* list, Equip* equip)
{
	Node* node = ID_Sreach(list, equip->id);
	if (node)
	{
		Equip* equipResult = node->pEquip;
		equipResult->type = equip->type;
		equipResult->name = equip->name;
		equipResult->price = equip->price;
		equipResult->buy_date = equip->buy_date;
		equipResult->scrap_date = equip->scrap_date;
	}
	else
	{
		Node* node = MakeNode(equip);
		if (strcmp(equip->id, list->head->pEquip->id) < 0)//头节点处理
		{
			node->next = list->head;
			list->head = node;
			//写入文件，行数0
		}
		else
		{
			Node* curr = list->head;
			int countLine = 1;
			while (curr)
			{
				if (strcmp(equip->id, curr->next->pEquip->id) < 0)//添加
				{
					node->next = curr->next;
					curr->next = node;
					//写入文件，行数countLine
					return;
				}
				curr = curr->next;
				countLine++;
			}
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

static Node* ID_Sreach(LinkList* list, char* id)
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

static void ID_sort(Equip* equip[])
{

}

void Date_sort(Equip* equip[])
{
}