#pragma once

Node* SearchById(LinkList* list, const char* id);

long long GetEquipNo(LinkList* list, const char* id);

bool AddEquip(LinkList* list, const Equip* equip);

unsigned char* TypeCount(LinkList* list);

void Date_sort(LinkList* list);

LinkList SearchByName(LinkList* list, const char* name);

void ScarpEquip(LinkList* list);

bool IsScarp(const Equip* equip);