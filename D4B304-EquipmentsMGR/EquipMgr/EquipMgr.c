#include "..\Main.h"
#include "EquipMgr.h"

void InputInfo()
{
}

void AddEquip(Equip* equip[], Equip* equipment)
{

}

unsigned char* TypeCount(LinkList* list)
{
	Node* curr = list->head;
	unsigned char* TYPE = (unsigned char*)calloc(TOTAL * 2 + 2, sizeof(unsigned char));
	assert(TYPE);
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