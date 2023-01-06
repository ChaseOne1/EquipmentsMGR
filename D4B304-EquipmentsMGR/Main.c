#include <windows.h>
#include "Main.h"
#include "EquipMgr\EquipMgr.h"
#include "EquipMgr\Equipment.h"
#include "UserInterface\UserInterface.h"
#include "DataMgr\FileMgr.h"

LinkList equipList;
const char dataFile[] = "Equipments_Info.txt";
void System_Initialize(const char* srcFile);
void System_Destory();


int main(int atgc, char* argv[])
{
	SetConsoleOutputCP(65001);//修改控制台的编码格式为utf-8
	System_Initialize("data.txt");
	while (true)
	{
		SetupUI();
		printf("> 请输入欲执行的操作： ");
		if (SystemControl(getchar()))
			break;
	}
	System_Destory();
	return 0;
}

void System_Initialize(const char* srcFile)
{
	equipList.LinkNum = 0;
	long long readLine = 1;
	Equip* equip = NULL;
	while (equip = ReadInfo(dataFile, readLine))
	{
		AddEquip(&equipList, equip);
		++readLine;
	}
	if (!srcFile)	return;
	readLine = 1;
	long long lineNo = 0;
	while (equip = ReadInfo(srcFile, readLine))
	{
		if (AddEquip(&equipList, equip))
		{
			lineNo = GetEquipNo(&equipList, equip->id);
			InsertInfo(dataFile, equip, lineNo);
		}
		++readLine;
	}
}

void System_Destory()
{
	Node* curr = equipList.head, * next;
	while (curr)
	{
		next = curr->next;
		free(curr->pEquip->name);
		free(curr->pEquip->id);
		free(curr->pEquip);
		free(curr);
		curr = next;
	}
}