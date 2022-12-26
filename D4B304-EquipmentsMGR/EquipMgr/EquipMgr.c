#include "..\Main.h"
#include "EquipMgr.h"

void InputInfo()
{
}

void AddEquip(Equip* equip[], Equip* equipment)
{

}

unsigned char* TypeCount(Equip* equip[], int EquipNum)
{
	unsigned char* TYPE = (unsigned char*)malloc(sizeof(unsigned char) * TOTAL * 2);
	if (!TYPE)
		return NULL;
	memset(TYPE, 0, sizeof(unsigned char) * 10);
	for (int i = 0; i < EquipNum; ++i)
	{
		switch (equip[i]->type)
		{
		case MEC:	++TYPE[MEC];	
			if (equip[i]->flag) ++TYPE[MEC + TOTAL];	break;
		case CHM:	++TYPE[CHM];
			if (equip[i]->flag) ++TYPE[CHM + TOTAL];	break;
		case MDC:	++TYPE[MDC];
			if (equip[i]->flag) ++TYPE[MDC + TOTAL];	break;
		case ELC:	++TYPE[ELC];
			if (equip[i]->flag) ++TYPE[ELC + TOTAL];	break;
		case SPC:	++TYPE[SPC];
			if (equip[i]->flag) ++TYPE[SPC + TOTAL];	break;
		default:	break;
		}
	}
	return TYPE;
}

static void ID_sort(Equip* equip[])
{

}

void Date_sort(Equip* equip[])
{
}