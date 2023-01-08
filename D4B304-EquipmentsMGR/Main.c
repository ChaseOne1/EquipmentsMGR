#include "Main.h"
#include "EquipMgr\EquipMgr.h"
#include "DataMgr\FileMgr.h"
#include "UserInterface\UserInterface.h"

static LinkList* pMainList;
const char gsDataFileName[] = "Equipments_Info.txt";
const char gsOutputFileName[] = "EquipmentsInfo_SortByDate.txt";

void System_Initialize(const char* srcFileName);
void System_Destory();


int main(int atgc, char* argv[])
{
	system("chcp 65001");//修改控制台的编码格式为utf-8
	//SetConsoleOutputCP(65001);
	System_Initialize(atgc > 1 ? argv[1] : NULL);
	SetupUI(pMainList);
	char ctrl = 0;
	while (true)
	{
		system("cls");
		MainMenuDisplay();
		printf("> 请输入欲执行的操作： ");
		if (SystemControl(getchar()))	break;
		UpdateDataFile(pMainList);
		printf("\n请按任意键继续...");
		while ((ctrl = getchar()) != '\n' && ctrl != EOF);
	}
	System_Destory();
	return 0;
}

void System_Initialize(const char* srcFileName)
{
	pMainList = MakeList(NULL, NULL);
	Equip* equip = NULL;
	FILE* dataFile = NULL;
	if (!(dataFile = fopen(gsDataFileName, "r")))
		dataFile = fopen(gsDataFileName, "w");
	//读取dataFile数据
	while ((equip = MakeEquip()) && InputEquip(equip, dataFile))
		AddEquip(pMainList, equip);
	FreeEquip(&equip);
	if (srcFileName)
	{
		FILE* srcFile = fopen(srcFileName, "r");
		assert(srcFile);
		//读取srcFile数据
		while ((equip = MakeEquip()) && InputEquip(equip, srcFile))
			AddEquip(pMainList, equip);
		FreeEquip(&equip);
		fclose(srcFile);
	}
	fclose(dataFile);
	UpdateDataFile(pMainList);
}

void System_Destory()
{
	FreeList(&pMainList, true);
	pMainList = NULL;
}