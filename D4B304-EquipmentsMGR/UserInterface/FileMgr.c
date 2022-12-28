#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void InputInformation(Equip eqp[],int n);
void WritetoFile(Equip eqp[], int n);
void YorN(int *px);

int main(void)
{
	Equip eqp[200];
	int n,x=0;
	for(;x==0;)
	{
		printf("要输入多少台设备?");
		scanf("%d",&n);
		InputInformation(eqp,n);
		WritetoFile(eqp,n);
		x++;
		YorN(&x);
	}
	return 0;
}

//输入
void InputInformation(Equip eqp[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("请输入一行第%d台的信息: \n",i+1);
		scanf("%d",	&eqp[i].type) ;
		scanf(" %c",	&eqp[i].name);
		scanf(" %c",	&eqp[i].id); //%c前有一个空格
		scanf("%lld",	&eqp[i].buy_date);
		scanf("%lld",	&eqp[i].scrap_date);
		scanf("%lf",	&eqp[i].price);
		scanf("%d",	&eqp[i].flag);
	}
}

//输出
void WritetoFile(Equip eqp[], int n)
{
	FILE *fp;
	int i;
    fp=fopen("aha.txt","a");
	if(fp==NULL)//以写方式打开文本文件
	{
		printf("打不开！\n");
		exit(0);
	}
	fprintf(fp,"\n以下是最新一次输入的输出结果\n\n输入了%d台设备的信息\n",n);//写入文件
	for(i=0;i<n;i++)
	{
		fprintf(fp,"%d %c %c %lld %lld %.2f %d\n",	eqp[i].type,
								eqp[i].name,
								eqp[i].id,
								eqp[i].buy_date,
								eqp[i].scrap_date,
								eqp[i].price,
								eqp[i].flag
				);
	}
	printf("已输出\n");
	fclose(fp);
}

//要不要继续
void YorN(int *px)
{
	printf("还要继续输入吗？(Y/N)");
	if(getchar()=='Y'||getchar()=='y')
	{
		*px=0;
	}
	else
	{
		*px=1;
	}
}
