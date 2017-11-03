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
	int levelIndex;
	_EnemyData enemies[MAX_ENEMIES];
	int map[MAX_TILES_PER_ROW][MAX_TILES_PER_COL];
	

};


class FileManager
{
public:
	FileManager() = default;
	static void WriteLevelData(const char* filename, _LevelFileData& data);
	static void ReadLevelData(const char* filename, _LevelFileData& data);
	static void WritePlayerData(const char* filename, struct MainPlayerData& data);
	static void ReadPlayerData(const char* filename, struct MainPlayerData& data);
};