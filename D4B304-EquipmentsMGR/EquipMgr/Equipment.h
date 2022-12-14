#pragma once

//设备种类
typedef enum EquipmentType
{
	MEC,	//机械类
	CHM,	//化学类
	MDC,	//医学类
	ELC,	//电子类
	SPC		//特殊类
}EquipType;


//设备结构体
typedef struct Equipment
{
	EquipType	type;//设备种类
	char*		name;//设备名称
	char*		id;//设备编号
	long long	buy_date;//购入日期
	long long	scrap_date;//保费日期
	double		price;//购入价格
	bool		flag;//保费标志
}Equip;