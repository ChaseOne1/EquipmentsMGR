#pragma once
#include "..\Main.h"

extern const char gsDataFileName[];
extern const char gsOutputFileName[];

/**
* @Function: AppendInfo（回调函数）
* @Brief:	 向参数文件尾追加参数对象的信息
* @Param1:	 欲读取的对象(Node* / Equip**)
* @Param2:	 欲追加到的文件指针
* @Return:	 当前处理的节点
**/
Node* AppendInfoToFile(Equip** data, FILE* file);


/**
* @Function: UpdateDataFile
* @Brief:	 当链表有变化时，更新dataFile的内容
* @Param1:	 欲读取的链表
* @Return:	 void
**/
void UpdateDataFile(LinkList* list);