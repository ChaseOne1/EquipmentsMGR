#include <stdlib.h>
#include "Equipment.h"

Equip* MakeEquip(void)
{
	Equip* equip = (Equip*)calloc(1, sizeof(Equip));
	return equip;
}

void FreeEquip(Equip* equip)
{
	//if equip is NULL , NO DOUBLE FREE！
	free(equip->name);
	free(equip->id);
	free(equip);
	equip = NULL;
}