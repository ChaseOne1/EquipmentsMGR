#pragma once
#include "..\Main.h"

extern FILE* dataFile;
extern FILE* outputFile;
extern const char dataFileName[];
extern const char outputFileName[];


Equip* ReadInfo(const char* fileName, const long long destLine);


/**
* @Function: AppendInfo
* @Brief:	 向参数文件尾追加参数设备的信息（链表回调函数）
* @Param1:	 欲追加信息的设备的二级指针
* @Param2:	 欲追加到的文件指针
* @Return:	 当前处理的节点
**/
Node* AppendInfo(Equip** data, FILE* file);


/**
* @Function: UpdateInfoFile
* @Brief:	 使用链表中的设备信息更新dataFile的文件内容
* @Param1:	 欲读取的链表
* @Return:	 void
**/
void UpdateInfoFile(LinkList* list);

void InsertInfo(const char* fileName, const Equip* equip, const long long destLine);

void DeleteInfo(const char* fileName, const long long destLine);
