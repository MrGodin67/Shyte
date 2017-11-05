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
	Vec2f exitPos;
	Vec2i rowsColumns;
	float surfaceFriction;
	int levelIndex;
	_EnemyData enemies[MAX_ENEMIES];
	int map[MAX_TILES_PER_ROW][MAX_TILES_PER_COL];
	

};
struct _GameData
{
	int numbUsers = 0;
	char userNames[10][255];

};

class FileManager
{
public:
	FileManager() = default;
	static bool WriteLevelData(const char* filename, _LevelFileData& data);
	static bool ReadLevelData(const char* filename, _LevelFileData& data);
	static bool WritePlayerData(const char* filename, struct MainPlayerData& data);
	static bool ReadPlayerData(const char* filename, struct MainPlayerData& data);
	static bool WriteGameData(const char* filename, _GameData& data);
	static bool ReadGameData(const char* filename, _GameData& data);
};