#pragma once

//Search Lable
#define NAME Name_cmp
#define ISSCRAPPED IsScarpped_cmp


/**
* @Function: AddEquip
* @Brief:	 向参数链表中添加/更新参数设备，始终保持链表按id升序排列
* @Param1:	 欲添加到的链表
* @Param2:	 欲添加的设备
* @Return:	 操作名称: 0 UPDATE-更新设备 ,	1 INSERT-插入设备
**/
bool AddEquip(LinkList* list, const Equip* equip);


/**
* @Function: DeleteEquip
* @Brief:	 删除参数链表中的参数节点设备，始终保持链表节点按数据的id升序排列
* @Param1:	 含有欲删除元素的链表
* @Param2:	 欲删除的设备的节点
* @Return:	 操作结果 false-删除失败 , true-删除成功
**/
bool DeleteEquip(LinkList* list, const Node* node);


/**
* @Function: TypeCount
* @Brief:	 统计参数链表中的各类设备数量及其状态
* @Param1:	 欲统计的链表
* @Return:	 长度为12的堆区数组，按设备种类值为下标储存该类设备的数量 \
			 按设备种类值+6储存该类设备中报废的设备数量 \
			 TOTAL下标对应值储存总设备数，TOTAL+6下标对应值储存总设备数中的报废设备数量
**/
unsigned char* TypeCount(LinkList* list);


/**
* @Function: Date_sort
* @Brief:	 将参数链表中的设备按照购入日期升序排列并储存其指针到堆区数组并返回
* @Param1	 欲排列的链表
* @Return:	 堆区的按购入日期升序排列的设备指针数组
**/
Equip** Date_sort(LinkList* list);


/**
* @Function: ScarpEquip
* @Brief:	 更改参数设备报废信息(根据报废日期更新报废状态)
* @Param1:	 欲更改的设备
* @Param2:	 报废日期
* @Return:	 void
**/
void ScarpEquip(Equip* equip, long long scrap_date);


/**
* @Function: SearchById
* @Brief:	 在参数链表中查询匹配参数id的设备节点
* @Param1:	 欲查询的链表
* @Param2:	 欲查询的id
* @Return:	 匹配id的节点
**/
Node* SearchById(LinkList* list, const char* id);


/**
* @Function: Name_cmp（回调函数）
* @Brief:	 比较参数节点设备名称和参数pData，如果匹配则返回参数节点
* @Param1:	 欲比较的节点
* @Param1:	 用户自定义参数
* @Return:	 匹配的参数节点
**/
Node* CALLBACK Name_cmp(Node* node, void* pData);


/**
* @Function: Scarpped_cmp（回调函数）
* @Brief:	 比较参数节点设备报废状态和参数pData，如果匹配则返回参数节点
* @Param1:	 欲比较的节点
* @Param1:	 用户自定义参数
* @Return:	 匹配的参数节点
**/
Node* CALLBACK IsScarpped_cmp(Node* node, void* pData);