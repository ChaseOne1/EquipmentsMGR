#include <windows.h>
#include "Main.h"
#include "EquipMgr\EquipMgr.h"
#include "EquipMgr\Equipment.h"
#include "UserInterface\UserInterface.h"
#include "DataMgr\FileMgr.h"

static LinkList* mainList;
const char dataFileName[] = "Equipments_Info.txt";
const char outputFileName[] = "EquipmentsInfo_SortByDate.txt";

void System_Initialize(const char* srcFileName);
void System_Destory();


int main(int atgc, char* argv[])
{
	SetConsoleOutputCP(65001);//修改控制台的编码格式为utf-8
	System_Initialize("data.txt");
	SetupUI(&mainList);
	char ctrl = 0;
	while (true)
	{
		system("cls");
		MainMenuDisplay();
		printf("> 请输入欲执行的操作： ");
		if (SystemControl(getchar()))	break;
		printf("\n请按任意键继续...");
		while ((ctrl = getchar()) != '\n' && ctrl != EOF);
	}
	System_Destory();
	return 0;
}

void System_Initialize(const char* srcFileName)
{
	mainList=(LinkList*)calloc(1,sizeof())
	dataFile = fopen(dataFileName, "r+");
	assert(dataFile);
	Equip* equip = NULL;
	while (equip = MakeEquip() && InputEquip(equip, dataFile))
		AddEquip(&mainList, equip);
	if (!srcFileName)	return;
	FILE* srcFile = fopen(srcFileName, "r");
	while (equip = MakeEquip() && InputEquip(equip, srcFile))
		AddEquip(&mainList, equip);
	UpdateInfoFile(&mainList);
	fclose(srcFile);
	fclose(dataFile);
}

void System_Destory()
{
	fclose(dataFile);
	fclose(outputFile);
	FreeList(&mainList);
}