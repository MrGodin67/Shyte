#pragma once

#include "includes.h"
#include "Vec2.h"

struct _EnemyData
{
	Vec2f position;
	int type;
};
struct _LevelFileData
{
	Vec2f tileDimensions;
	Vec2f playerPos;
	Vec2i rowsColumns;
	float surfaceFriction;
	_EnemyData enemies[MAX_ENEMIES];
	int map[MAX_TILES_PER_ROW][MAX_TILES_PER_COL];
	

};


class FileManager
{
public:
	FileManager() = default;
	static void WriteLevelData(const char* filename, _LevelFileData& data)
	{
		FILE* file;
		fopen_s(&file,filename, "wb");
		assert(file);
		fwrite(&data, sizeof(_LevelFileData),1, file);
		fclose(file);
	};
	static void ReadLevelData(const char* filename, _LevelFileData& data)
	{
		FILE* file;
		fopen_s(&file,filename, "rb");
		assert(file);
		fread(&data, sizeof(_LevelFileData), 1, file);
		fclose(file);
	};
};