#pragma once

void AddEquip(LinkList* list, Equip* equip);

unsigned char* TypeCount(LinkList* list);

void Date_sort(Equip* equip[]);

LinkList SearchByName(LinkList* list, char* name);

void ScarpEquip(LinkList* list);

bool IsScarp(Equip* equip);