#include "..\Main.h"
#include "List.h"

Node* MakeNode(Equip* equip)
{
	Node* node = (Node*)malloc(sizeof(Node));
	assert(node);
	node->pEquip = equip;
	node->next = NULL;
	return node;
}
