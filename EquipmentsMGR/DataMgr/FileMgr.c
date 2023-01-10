#include "FileMgr.h"

extern const char* cEquipType[TOTAL + 1];

static long long lastNum = 0, currNum = 0;


Node* AppendInfoToFile(Equip** data, FILE* file)
{
	Equip* equip = *data;
	fprintf(file, "%-4s\t%-6s\t%-6s\t%-10lld\t%-8lld\t%.3lf\n", cEquipType[equip->type], equip->name, equip->id,
		equip->buy_date, equip->scrap_date, equip->price);//写入文件信息
	return (Node*)data;
}

void UpdateDataFile(LinkList* list)
{
	lastNum = currNum;
	currNum = list->LinkNum;
	if (lastNum == currNum)	return;
	FILE* dataFile = fopen(gsDataFileName, "w");
	assert(dataFile);
	ListForAllNodeV(list, AppendInfoToFile, dataFile);
	fclose(dataFile);
}