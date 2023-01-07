#include "FileMgr.h"

FILE* dataFile = NULL;
FILE* outputFile = NULL;
extern const char* cEquipType[TOTAL + 1];

static long long dtoend(FILE* fp)
{
	long long curpos = ftell(fp); // Get current position
	fseek(fp, 0, SEEK_END);      // Go to the file's end
	long long endpos = ftell(fp);     // Gets the file's size
	fseek(fp, curpos, SEEK_SET); // Restore previous pos
	return endpos - curpos;      // Return the distance!
}

Equip* ReadInfo(FILE* file, const long long destLine)
{
	//SPC Equip1 id001 2234 31254
	assert(file);
	long long line = 1;
	char ch;
	while (line != destLine && !feof(file))
		while ((ch = getc(file)) == '\n')
			line++;

	if (feof(file))
	{
		fclose(file);
		return NULL;
	}
	fseek(file, -1, SEEK_CUR);
	char type[4];
	fscanf(file, "%s", type);
	if (feof(file))
	{
		return NULL;
	}
	Equip* equip = (Equip*)malloc(sizeof(Equip));
	equip->type = -1;
	for (int i = 0; i < TOTAL; ++i)
	{
		if (!strcmp(type, cEquipType[i]))
		{
			equip->type = i;
			break;
		}
	}
	char buffer[255];
	fscanf(file, "%s", buffer);
	equip->name = (char*)malloc(strlen(buffer) + 1);
	assert(equip->name);
	strcpy(equip->name, buffer);
	fscanf(file, "%s", buffer);
	equip->id = (char*)malloc(strlen(buffer) + 1);
	assert(equip->id);
	strcpy(equip->id, buffer);

	fscanf(file, "%lld %lld %lf", &equip->buy_date, &equip->scrap_date, &equip->price);
	equip->flag = equip->scrap_date;
	if (equip->type == -1)
	{
		free(equip->id);
		free(equip->name);
		free(equip);
		return NULL;
	}
	return equip;
}


Node* AppendInfo(Equip** data, FILE* file)
{
	Equip* equip = *data;
	fprintf(file, "%-4s\t%-6s\t%-6s\t%-10lld\t%-8lld\t%.3lf\n", cEquipType[equip->type], equip->name, equip->id,
		equip->buy_date, equip->scrap_date, equip->price);//写入文件信息
	return (Node*)data;
}


void InsertInfo(FILE* file, const Equip* equip, const long long destLine)
{
	assert(file);
	long long line = 1;
	while (line != destLine && !feof(file))
		while (getc(file) == '\n')
			line++;
	if (feof(file))
	{
		fclose(file);
		AddInfo(file, "a+", equip);
		return;
	}

	fseek(file, -1, SEEK_CUR);
	long long bufSize = dtoend(file);//后续字节长度
	long long currPos = ftell(file);//当前位置
	char* buffer = (char*)malloc(bufSize);
	fread(buffer, sizeof(char), bufSize, file);//保存后续部分
	fseek(file, currPos, SEEK_SET);//重置文件指针
	fprintf(file, "%-4s\t%-6s\t%-6s\t%-10lld\t%-8lld\t%.3lf\n", cEquipType[equip->type], equip->name, equip->id,
		equip->buy_date, equip->scrap_date, equip->price);//写入文件信息
	fwrite(buffer, sizeof(char), bufSize, file);//复原后续部分
	free(buffer);
}

void DeleteInfo(FILE* file, const long long destLine)
{
}

void UpdateInfoFile(LinkList* list)
{
	fclose(dataFile);
	dataFile = fopen(dataFileName, "w");
	ListForAllNode(list, AppendInfo, dataFile);
	fclose(dataFile);
}
