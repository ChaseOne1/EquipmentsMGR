#pragma once
#include <stdbool.h>

//设备种类
typedef enum EquipmentType
{
	MEC,	//机械类
	CHM,	//化学类
	MDC,	//医学类
	ELC,	//电子类
	SPC,	//特殊类
	TOTAL	//总类数
}eEquipType;


//设备结构体
typedef struct Equipment
{
	eEquipType	type;		//设备种类
	char* name;				//设备名称
	char* id;				//设备编号
	long long	buy_date;	//购入日期
	long long	scrap_date;	//报废日期
	double		price;		//购入价格
	bool		flag;		//报废标志
}Equip;


/**
* @Function: MakeEquip
* @Brief:	 构造并初始化一个设备
* @Param:	 void
* @Return:	 构造的设备
**/
Equip* MakeEquip(void);


/**
* @Function: FreeEquip
* @Brief:	 销毁释放设备
* @Param1:	 equip 欲销毁释放的设备
* @Return:	 void
**/
void FreeEquip(Equip* equip);