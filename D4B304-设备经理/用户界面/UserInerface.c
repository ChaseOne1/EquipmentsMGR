#include "..\\Main.h"
#include "..\\EquipMgr\\Equipment.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
void BOOL(LinkList List)
{
	struct tm t;   
	time_t now; 
	time(&now);     
	localtime_s(&t, &now); 
	int a,x,y,z,sum;
	x=t.tm_year + 1900;
	y=t.tm_mon + 1;
	z=t.tm_mday;
	sum=10000*x+y*100+z;
	Node *sky=(Node*)malloc(sizeof(Node));
	sky=List.head;
	while(sky->pequip->scrap_date)
	{
		a=sky->pequip->scrap_date;
	if(a<sum)
		List.head->pequip->flag=0;
	sky=sky->next;
	}
	
}
