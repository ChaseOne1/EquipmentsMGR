#include "..\Main.h"
#include "UserInterface.h"
#include "..\EquipMgr\EquipMgr.h"
#include "..\DataMgr\FileMgr.h"

const char* cEquipType[TOTAL + 1] = { "MEC","CHM","MDC","ELC","SPC","TOTAL" };

void SetupUI()
{
	system("cls");
	MainMenuDisplay();
}



void MainMenuDisplay()
{
	printf("--------------设备管理系统------------------\n");
	printf("|					   |\n");
	printf("|	  1.添加设备：添加设备信息	   |\n");
	printf("|	  2.删除设备：删除设备信息	   |\n");
	printf("|	  3.统计设备：分类统计设备	   |\n");
	printf("|	  4.设备报废：对设备报废处理       |\n");
	printf("|	  5.设备查询：按条件查询设备       |\n");
	printf("|	  6.设备排序：按日期排序设备       |\n");
	printf("|	  7.浏览设备：浏览全部设备         |\n");
	printf("|	  0.退出系统：退出	           |\n");
	printf("|					   |\n");
	printf("--------------------------------------------\n");
}

void PrintInfo(Equip* equip)
{
	printf("%-8s\t", cEquipType[equip->type]);
	printf("%-8s\t", equip->name);
	printf("%-8s\t", equip->id);
	printf("%-10lld\t", equip->buy_date);
	printf("%-8lld\t", equip->scrap_date);
	printf("%.3lf\t", equip->price);
	putchar('\n');
	putchar('\n');
}

static void Search()
{
	printf("支持的查询方式有：1.设备名称  2.报废标志\n请选择：");
	char ctrl = getchar();
	if (ctrl != '\n')	getchar();
	else return;
	if (ctrl == '1')
	{
		printf("请输入欲查询的设备名称：\n> ");
		char name[255];	gets(name);
		LinkList list = SearchByName(&equipList, name);
		if (list.tail == list.head)
			printf("无该名称设备!\n");
		else
		{
			printf("查询结果如下：\n\n");
			printf("设备种类\t设备名称\t设备编号\t购入日期\t销毁日期\t购入价格\n");
			Node* curr = list.head->next;
			while (curr)
			{
				PrintInfo(curr->pEquip);
				curr = curr->next;
			}
			//释放链表节点
			Node* curr1 = equipList.head, * next;
			while (curr1)
			{
				next = curr1->next;
				free(curr1);
				curr1 = next;
			}
		}
	}
	else if (ctrl == '2')
	{
		printf("\n请选择报废标志：已报废(Y)/未报废(N)\n> ");
		char flag = getchar();
		if (flag != '\n')	getchar();
		else return;
		if (flag == 'Y' || flag == 'y')
		{
			Node* curr2 = equipList.head;
			while (curr2)
			{
				if (IsScarp(curr2->pEquip))
					PrintInfo(curr2->pEquip);
				curr2 = curr2->next;
			}
		}
		else if (flag == 'N' || flag == 'n')
		{
			Node* curr3 = equipList.head;
			while (curr3)
			{
				if (!IsScarp(curr3->pEquip))
					PrintInfo(curr3->pEquip);
				curr3 = curr3->next;
			}
		}
	}
	system("pause");
}

static void Count()
{
	system("cls");
	char type[6];
	unsigned char* result = TypeCount(&equipList);
	printf("请输入欲统计的类别： (机械类:MEC、化学类:CHM、医学类:MDC、电子类:ELC、特殊类:SPC、所有:TOTAL)\n退出请输入N\n");
	while (true)
	{
		eEquipType TYPE = -1;
		printf("> ");
		gets(type);
		//getchar();
		for (int i = 0; i < TOTAL + 1; ++i)
		{
			if (!strcmp(type, cEquipType[i]))
			{
				TYPE = i;
				break;
			}
		}
		if (type[0] == 'N' || type[0] == 'n')
			break;
		if (TYPE != -1)
			printf("%s 设备共有 %d 台（报废 %d 台）\n",
				cEquipType[TYPE], result[TYPE], result[TYPE + TOTAL + 1]);
		else
			printf("请重新输入\n");
	}
	free(result);
	result = NULL;
}

static void ShowAll()
{
	printf("设备种类\t设备名称\t设备编号\t购入日期\t销毁日期\t购入价格\n");
	Node* curr = equipList.head;
	while (curr)
	{
		PrintInfo(curr->pEquip);
		curr = curr->next;
	}
	printf("已全部显示完毕！\n");
	system("pause");
}

static void InputInfo()
{
	char type[4];
	printf("请输入设备信息...\n格式：设备种类 设备名称 设备编号 购入日期 购入价格\n(设备种类：机械类:MEC、化学类:CHM、医学类:MDC、电子类:ELC、特殊类:SPC)\n");
	printf("输入示例: CHM Equip1 ID1900111 20221219 648.0\n录入完毕请输入N\n");
	do
	{
		printf("> ");
		scanf("%s", &type);
		if (type[0] == 'N' || type[0] == 'n')	break;//录入完毕
		Equip* equip = (Equip*)malloc(sizeof(Equip));

		//类型输入
		equip->type = -1;
		for (int i = 0; i < TOTAL; ++i)
		{
			if (!strcmp(type, cEquipType[i]))
			{
				equip->type = i;
				break;
			}
		}
		//名称和编号输入
		char buffer[255];
		scanf("%s", buffer);
		equip->name = (char*)malloc(strlen(buffer) + 1);
		assert(equip->name);
		strcpy(equip->name, buffer);
		scanf("%s", buffer);
		equip->id = (char*)malloc(strlen(buffer) + 1);
		assert(equip->id);
		strcpy(equip->id, buffer);

		//购入日期和价格读入
		scanf("%lld%lf", &equip->buy_date, &equip->price);
		getchar();
		//报废初始设置
		equip->scrap_date = 0;
		equip->flag = false;

		printf("确认输入？(Y/N)\n");
		char ctrl = getchar();
		if (ctrl != '\n')	getchar();
		if (ctrl == 'Y' || ctrl == 'y')
		{
			if (equip->type == -1)
			{
				printf("类型输入有误，请重新输入！\n");
				free(equip->name);
				free(equip->id);
				free(equip);
			}

			else
			{
				if (AddEquip(&equipList, equip))
					printf("已录入！\n");
				else
					printf("已更新！\n");
				InsertInfo(dataFile, equip, GetEquipNo(&equipList, equip->id));
			}
		}
		else if (ctrl == 'N' || ctrl == 'n')
		{
			free(equip->name);
			free(equip->id);
			free(equip);
		}
		putchar('\n');
	} while (true);
}

static void Deletee()
{
	do
	{
		char id[255];
		printf("请输入欲删除的设备的编号\n退出请输入N");
		printf("\n> ");
		gets(id);
	//	getchar();//gets会留下\n
		if (id[0] == 'N' || id[0] == 'n') break; //退出
		Node* result = SearchById(&equipList, id);
		if (result)
		{
			printf("请确认删除对象：(Y/N)\n\n");
			printf("设备种类\t设备名称\t设备编号\t购入日期\t销毁日期\t购入价格\n");
			PrintInfo(result->pEquip);
			printf("> ");
			char ctrll = getchar();
			if (ctrll != '\n')	getchar();
			if (ctrll == 'Y' || ctrll == 'y')
			{
				Node* curr = equipList.head;
				if (curr == result)
					equipList.head = equipList.head->next;
				else
					//遍历链表寻找目标节点得前驱节点（curr）
					while (curr)
					{
						
						if (curr->next == result)//普通节点处理
						{
							if (result != equipList.tail)
							{
								curr->next = result->next;
								break;
							}
							else//尾节点处理
							{
								curr->next = NULL;
								equipList.tail = curr;
								break;
							}
						}
						curr = curr->next;
					}
				long long line = GetEquipNo(&equipList, result->pEquip->id);
				free(result->pEquip->id);
				free(result->pEquip->name);
				free(result->pEquip);
				free(result);
				equipList.LinkNum--;
				DeleteInfo(dataFile, line);
				printf("已删除！\n");
			}
		}
		else
			printf("未找到id为%s的设备！\n", id);

		//printf("继续删除？(Y/N) > ");
		//char ctrl = getchar();
		//if (ctrl != '\n')	getchar();
		//if (ctrl == 'N' || ctrl == 'n')
		//	break;
		putchar('\n');
	} while (true);

}

static void Scrap()
{
	system("cls");
	do 
	{
		printf("请输入欲报废的设备的编号\n退出请输入N");
		printf("> ");
		char id[255];
		gets(id);
		if (id[0] == 'N' || id[0] == 'n') break; //退出
		Node* result = SearchById(&equipList, id);
		if (result)
		{
			printf("请确认报废对象：(Y/N)\n\n");
			printf("设备种类\t设备名称\t设备编号\t购入日期\t销毁日期\t购入价格\n");
			PrintInfo(result->pEquip);
			printf("请输入报废日期（格式20221212）: > ");
			long long date;
			scanf("%lld", &date);
			result->pEquip->scrap_date = date;
			result->pEquip->flag = true;
			long long no = GetEquipNo(&equipList, result->pEquip->id);
			InsertInfo("Equipments_Info.txt", result->pEquip, no);
			printf("已修改设备状态！");
		}
		else
			printf("没有编号为:%s的设备！", id);
		putchar('\n');
	} while (true);
	
}

static void Sort()
{
	printf("正在处理请稍后...\n");
	Date_sort(&equipList);
	printf("结果已输出到文件“Equipments_Info_SortByDate.txt“");
	system("pause");
}

bool SystemControl(char ctrl)
{
	system("cls");
	if (ctrl != '\n')	getchar();
	switch (ctrl)
	{
	case '1':
		InputInfo();
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
		printf("确认退出？(Y/N)\n> ");
		char ch = getchar();	getchar();
		if (ch == 'Y' || ch == 'y')
			return true;
		else
			break;
	default:
		break;
	}
	return false;
}