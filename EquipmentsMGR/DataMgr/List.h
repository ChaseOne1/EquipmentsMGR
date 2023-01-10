#pragma once

//链表节点
typedef struct ListNode
{
	Equip* pEquip;
	struct ListNode* next;
}Node;

//链表
typedef struct NodeList
{
	Node* head;
	Node* tail;
	long long LinkNum;
}LinkList;


//操作链表的回调函数指针类型
typedef Node* (*NodeCallBack)(Node* node, void* pData);


/**
* @Function: MakeNode
* @Brief:	 结合传入的参数创建一个已初始化的堆区新节点,next置为NULL
* @Param1:	 新节点的数据部分
* @Return:	 堆区新节点
**/
Node* MakeNode(Equip* equip);


/**
* @Function: FreeNode
* @Brief:	 释放节点及其数据部分（均动态分配的）
* @Param1:	 节点所在链表（可为NULL）
* @Param2:	 欲释放的节点的二级指针
* @Param3:	 是否释放节点的数据部分
* @Return:	 void
**/
void FreeNode(LinkList* list, Node** node, bool flag);


/**
* @Function: MakeList
* @Brief:	 结合传入的参数创建一个已初始化的堆区新链表，LinkNum据参数自动结算
* @Param1:	 新链表的头节点，可为NULL（为NULL时不会配置尾节点）
* @Param2:	 新链表的尾节点，可为NULL
* @Return:	 动态配分的新链表
**/
LinkList* MakeList(Node* head, Node* tail);


/**
* @Function: FreeList
* @Brief:	 释放链表及其节点(均动态分配的)
* @Param1:	 欲释放的链表的二级指针
* @Param2:	 是否释放链表节点的数据部分
* @Return:	 void
**/
void FreeList(LinkList** pList, bool flag);


/**
* @Function: PushFront
* @Brief:	 将参数节点添加到链表头
* @Param1:	 欲操作的链表
* @Param2:	 准链表头
* @Return:	 void
**/
void PushFront(LinkList* list, Node* node);


/**
* @Function: PopFront
* @Brief:	 删除参数链表头节点
* @Param1:	 欲操作的链表
* @Param2:	 是否释放链表节点的数据部分
* @Return:	 void
**/
void PopFront(LinkList* list, bool flag);


/**
* @Function: PushBack
* @Brief:	 将参数节点添加到链表尾
* @Param1:	 欲操作的链表
* @Param2:	 准链表尾
* @Return:	 void
**/
void PushBack(LinkList* list, Node* node);


/**
* @Function: PopBack
* @Brief:	 删除参数链表尾节点
* @Param1:	 欲操作的链表
* @Param2:	 是否释放链表节点的数据部分
* @Return:	 void
**/
void PopBack(LinkList* list, bool flag);


/**
* @Function: ListForAllNodeL
* @Brief:	 为参数链表同步回调参数回调函数，并创建复制于回调函数返回的节点的堆区节点组成的堆区链表(这句话NO ERROR!!!)
* @Param1:	 欲操作的链表
* @Param2:	 回调函数，返回值应为当前处理的节点，参数1为当前节点 参数2为自定义数据
* @Param3:	 回调函数的参数2，自定义数据
* @Return:	 由复制的、储存在堆区的新节点组成的堆区链表，复制对象是回调函数返回的节点
**/
LinkList* ListForAllNodeL(LinkList* list, NodeCallBack pfCallBack, void* pData);


/**
* @Function: ListForAllNodeV
* @Brief:	 为参数链表同步回调参数回调函数
* @Param1:	 欲操作的链表
* @Param2:	 回调函数，返回值应为当前处理的节点，参数1为当前节点 参数2为自定义数据
* @Param3:	 回调函数的参数2，自定义数据
* @Return:	 void
**/
void ListForAllNodeV(LinkList* list, NodeCallBack pfCallBack, void* pData);


/**
* @Function: ListValToArry
* @Brief:	 将链表的所有数据值复制转换为堆区新数组
* @Param1:	 欲操作的链表
* @Return:	 堆区开辟的新数组
**/
Equip** ListValToArry(LinkList* list);