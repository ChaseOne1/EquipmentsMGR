#include "..\Main.h"
#include "UserInterface.h"
#include "..\EquipMgr\EquipMgr.h"
#include "..\DataMgr\FileMgr.h"

const char* cEquipType[TOTAL + 1] = { "MEC","CHM","MDC","ELC","SPC","TOTAL" };

static LinkList* pEquipList;

static void Input();	//添加
static void Deletee();	//删除
static void Count();	//统计
static void Scrap();	//报废
static void Search();	//搜索
static void Sort();		//排序
static void ShowAll();	//浏览
static bool Exit();		//退出

void SetupUI(const LinkList* list)
{
	pEquipList = list;
}

void MainMenuDisplay()
{
	printf("--------------设备管理系统------------------\n");
	printf("|					   |\n");
	printf("|	  1.添加设备：添加设备信息	   |\n");
	printf("|	  2.删除设备：删除设备信息	   |\n");
	printf("|	  3.统计设备：分类统计设备	   |\n");
	printf("|	  4.设备报废：修改报废状态	   |\n");
	printf("|	  5.设备查询：按条件查询设备       |\n");
	printf("|	  6.设备排序：按日期排序设备       |\n");
	printf("|	  7.浏览设备：浏览全部设备	   |\n");
	printf("|	  0.退出系统：退出	           |\n");
	printf("|					   |\n");
	printf("--------------------------------------------\n");
}

bool SystemControl(char ctrl)
{
	system("cls");
	switch (ctrl)
	{
	case '1':
		Input();
		break;
	case'2':
		Deletee();
		break;
	case '3':
		Count();
		break;
	case '4':
		Scrap();
		break;
	case '5':
		Search();
		break;
	case '6':
		Sort();
		break;
	case '7':
		ShowAll();
		break;
	case '0':
		return Exit();
	default:
		break;
	}
	system("pause");
	return false;
}

Node* PrintInfo(Equip** data, void* pData)
{
	Equip* equip = *data;
	printf("%-8s\t", cEquipType[equip->type]);
	printf("%-8s\t", equip->name);
	printf("%-8s\t", equip->id);
	printf("%-10lld\t", equip->buy_date);
	printf("%-8lld\t", equip->scrap_date);
	printf("%.3lf\t", equip->price);
	putchar('\n');
	putchar('\n');
	return data;
}

eEquipType StrToType(const char* type)
{
	for (int i = 0; i < TOTAL; ++i)
		if (!strcmp(type, cEquipType[i]))
			return i;
	return -1;
}

bool InputEquip(Equip* equip, FILE* stream)
{
	char buffer[255];

	fscanf(stream, "%s", buffer);
	equip->type = StrToType(buffer);//type

	if (equip->type == -1 || feof(stream))
		return false;

	fscanf(stream, "%s", buffer);
	equip->name = (char*)malloc(strlen(buffer) + 1);
	assert(equip->name);
	strcpy(equip->name, buffer);//name

	fscanf(stream, "%s", buffer);
	equip->id = (char*)malloc(strlen(buffer) + 1);
	assert(equip->id);
	strcpy(equip->id, buffer);//id

	fscanf(stream, "%lld %lld %lf", &equip->buy_date, &equip->scrap_date, &equip->price);//buy_date & scrap_date & price
	equip->flag = equip->scrap_date;//flag

	//fgetc(stream);

	return true;
}

static void Input()
{
	char type[4];
	printf("请输入设备信息...\n格式：设备种类 设备名称 设备编号 购入日期 销毁日期 购入价格\n(设备种类：机械类:MEC、化学类:CHM、医学类:MDC、电子类:ELC、特殊类:SPC)\n");
	printf("输入示例: CHM Equip1 ID1900111 20221219 20230107 648.0\n退出请输入N\n");
	do
	{
		printf("> ");
		char ch;
		while ((ch = getchar()) == '\n');
		if (ch == 'N' || ch == 'n')		break;//退出
		ungetc(ch, stdin);
		Equip* equip = MakeEquip();
		assert(equip);
		if (InputEquip(equip, stdin))
			if (AddEquip(pEquipList, equip))
				printf("已录入！\n");
			else
				printf("已更新！\n");
		else
		{
			printf("输入中出现错误，请重试！\n");
			FreeEquip(&equip);
		}
		putchar('\n');
	} while (true);
}

static void Deletee()
{
	do
	{
		char id[255] = { 0 };
		printf("请输入欲删除的设备的编号\n退出请输入N\n> ");
		scanf("%s", id);
		if (id[0] == 'N' || id[0] == 'n') break; //退出
		Node* result = SearchById(pEquipList, id);
		if (result)
		{
			printf("请确认删除对象：(Y/N)\n\n");
			printf("设备种类\t设备名称\t设备编号\t购入日期\t销毁日期\t购入价格\n");
			PrintInfo(&result->pEquip, NULL);
			printf("> ");
			char ch = 0;
			while ((ch = getchar()) == '\n');
			if (ch == 'Y' || ch == 'y')
			{
				FreeNode(pEquipList, &result, true);
				printf("已删除！\n");
			}
		}
		else
			printf("未找到id为%s的设备！\n", id);
		putchar('\n');
	} while (true);

}

static void Count()
{
	system("cls");
	char type[6] = { 0 };
	eEquipType TYPE = -1;
	unsigned char* result = TypeCount(pEquipList);
	printf("请输入欲统计的类别： (机械类:MEC、化学类:CHM、医学类:MDC、电子类:ELC、特殊类:SPC、所有:TOTAL)\n退出请输入N\n");
	while (true)
	{
		printf("> ");
		scanf("%s", type);
		TYPE = StrToType(type);
		if (type[0] == 'N' || type[0] == 'n')	break;
		if (TYPE != -1)
			printf("%s 设备共有 %d 台（报废 %d 台）\n",
				cEquipType[TYPE], result[TYPE], result[TYPE + TOTAL + 1]);
		else
			printf("请重新输入\n");
	}
	free(result);
	result = NULL;
}

static void Scrap()
{
	do
	{
		printf("请输入欲修改的设备的编号\n退出请输入N");
		printf("> ");
		char id[255] = { 0 };
		scanf("%s", id);
		if (id[0] == 'N' || id[0] == 'n') break; //退出
		Node* result = SearchById(pEquipList, id);
		if (result)
		{
			printf("请确认报废对象：(Y/N)\n\n");
			printf("设备种类\t设备名称\t设备编号\t购入日期\t销毁日期\t购入价格\n");
			PrintInfo(result, NULL);
			char ch = 0;
			while ((ch = getchar()) == '\n');
			if (ch == 'Y' || ch == 'y')
			{
				printf("请输入报废日期(格式20221212):> ");
				long long date = 0;
				scanf("%lld", &date);
				ScarpEquip(result->pEquip, date);
				printf("已修改设备状态！");
			}
		}
		else
			printf("没有编号为：%s的设备！", id);
		putchar('\n');
	} while (true);
}

static void Search()
{
	printf("支持的查询方式有：1.设备名称  2.报废标志\n请选择(按N退出): > ");
	char ctrl = 0;
	while ((ctrl = getchar()) == '\n');
	LinkList* resultList = NULL;
	if (ctrl == '1')
	{
		printf("请输入欲查询的设备名称：\n> ");
		char name[255] = { 0 };
		scanf("%s", name);
		resultList = ListForAllNodeL(pEquipList, NAME, name);
	}
	else if (ctrl == '2')
	{
		printf("\n请选择报废标志：已报废(Y) / 未报废(N)\n> ");
		while ((ctrl = getchar()) == '\n');
		if (ctrl == 'Y' || ctrl == 'y')
			resultList = ListForAllNodeL(pEquipList, ISSCRAPPED, true);
		else if (ctrl == 'N' || ctrl == 'n')
			resultList = ListForAllNodeL(pEquipList, ISSCRAPPED, false);
	}
	else
		return;
	printf("\n设备种类\t设备名称\t设备编号\t购入日期\t销毁日期\t购入价格\n");
	ListForAllNodeV(resultList, PrintInfo, NULL);
	FreeList(resultList, false);
	resultList = NULL;
}

static void Sort()
{
	printf("所有设备信息将会按购入日期升序排序！\n");
	printf("是否继续？(Y/N) > ");
	char ctrl = 0;
	while ((ctrl = getchar()) == '\n');
	if (ctrl == 'N' || ctrl == 'n')		return;
	FILE* outputFile = fopen(gsOutputFileName, "w");
	Equip** dateList = Date_sort(pEquipList);
	for (int i = 0; i < pEquipList->LinkNum; ++i)
		AppendInfoToFile(&dateList[i], outputFile);//param1 try "dateList++" haha
	fclose(outputFile);
	printf("结果已输出到文件%s\n", gsOutputFileName);
}

static void ShowAll()
{
	printf("设备种类\t设备名称\t设备编号\t购入日期\t销毁日期\t购入价格\n");
	ListForAllNodeV(pEquipList, PrintInfo, NULL);
	printf("已全部显示完毕！\n");
}

static bool Exit()
{
	printf("确认退出？(Y/N)\n> ");
	char ctrl = 0;
	while ((ctrl = getchar()) == '\n');
	if (ctrl == 'Y' || ctrl == 'y')
	{
		printf("正在退出...\n");
		return true;
	}
	else
		return false;
}