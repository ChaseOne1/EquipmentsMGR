#include "..\Main.h"
#include <string.h>
#include <stdlib.h>


//在输入所有设备信息之后，设备信息以编号从小到大的顺序进行排序
/*我在这里耽误了很多时间，最后借鉴了CSDN的代码；
源代码是以int类型进行排序，而我们的是以char类型数据进行排序，两者似乎不能通用？*/
int cmp(const void* a,const void* b)
{
	Equip *aa=(Equip *)a;
	Equip *bb=(Equip *)b;
	return (aa->id)>(bb->id);
}

void SortbyID(Equip,int n)//n是输入设备的数量、指输入了几个设备
{
	qsort(Equip,n,sizeof(Equip[0]),cmp);
	for(int i=0;i<n;i++)
	{
		printf("%s %c %c %d %d %f %d\n",Equip[i].type,Equip[i].name,Equip[i].id,Equip[i].buy_date,Equip[i].scrap_date,Equip[i].price,Equip[i].flag);
	}
}




/*按设备名称查询*/
void SearchbyName(int n)//n是输入设备的数量、指输入了几个设备
{
	char Name[10];
	int i;
	printf("请输入想要查询的设备名称:");
	scanf("%s",&Name);
	for(i=0;i<n;i++)
	{
		if(strcmp(Name,Equip[i].name)==0)
			printf("%s %c %c %d %d %f %d\n",Equip[i].type,Equip[i].name,Equip[i].id,Equip[i].buy_date,Equip[i].scrap_date,Equip[i].price,Equip[i].flag);
	}
	if(i==n||strcmp(Name,Equip[n].name)!=0)
		printf("未找到该设备\n");
}
