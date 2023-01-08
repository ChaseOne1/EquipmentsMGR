#include "..\Main.h"

Equip* MakeEquip(void)
{
	Equip* equip = (Equip*)calloc(1, sizeof(Equip));
	assert(equip);
	return equip;
}

void FreeEquip(Equip** pEquip)
{
	//if equip is NULL , NO DOUBLE FREE！
	Equip* equip = *pEquip;
	free(equip->name);
	free(equip->id);
	free(equip);
	equip = NULL;
	*pEquip = NULL;
}