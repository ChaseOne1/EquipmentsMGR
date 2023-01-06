#pragma once
#include "..\Main.h"


Equip* ReadInfo(const char* fileName, const long long destLine);

void AddInfo(const char* fileName, const char* mode ,const Equip* equip);

void InsertInfo(const char* fileName, const Equip* equip, const long long destLine);

void DeleteInfo(const char* fileName, const long long destLine);
