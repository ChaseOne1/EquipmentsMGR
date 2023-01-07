#pragma once

extern const char* cEquipType[TOTAL + 1];


/**
* @Function: SetupUI
* @Brief:	 设置UI系统工作的链表对象
* @Param1:	 链表对象
* @Return:	 void
**/
void SetupUI(const LinkList* list);

/**
* @Function: MainMenuDisplay
* @Brief:	 系统菜单界面显示
* @Param:	 void
* @Return:	 void
**/
void MainMenuDisplay(void);


/**
* @Function: SystemControl
* @Brief:	 系统指令控制
* @Param1:	 用户指令
* @Return:	 是否退出
**/
bool SystemControl(char ctrl);

/**
* @Function: StrToType
* @Brief:	 解析字符串对应设备类型
* @Param1:	 欲解析的字符串
* @Return:	 字符串对应设备类型
**/
eEquipType StrToType(const char* type);


/**
* @Function: InputEquip
* @Brief:	 从参数流中读取数据并填充参数设备
* @Param1:	 要填充的设备
* @Param2:	 欲读取的流
* @Return:	 填充状态
**/
bool InputEquip(Equip* equip, FILE* stream);