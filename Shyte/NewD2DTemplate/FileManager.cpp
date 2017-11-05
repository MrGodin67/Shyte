#include "FileManager.h"
#include "Player.h"
bool FileManager::WriteLevelData(const char * filename, _LevelFileData & data)

{
	FILE* file = nullptr;
	fopen_s(&file, filename, "wb");
	if (file == NULL)
		return false;
	fwrite(&data, sizeof(_LevelFileData), 1, file);
	fclose(file);
	return true;
}
bool FileManager::ReadLevelData(const char * filename, _LevelFileData & data)

{
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");
	if (file == NULL)
		return false;
	fread(&data, sizeof(_LevelFileData), 1, file);
	fclose(file);
	return true;
}
bool FileManager::WritePlayerData(const char * filename, MainPlayerData & data)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "wb");
	if (file == NULL)
		return false;
	fwrite(&data, sizeof(MainPlayerData), 1, file);
	fclose(file);
	return true;
}
bool FileManager::ReadPlayerData(const char * filename, MainPlayerData & data)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");
	if (file == NULL)
		return false;
	fread(&data, sizeof(MainPlayerData), 1, file);
	fclose(file);
	return true;
}
bool FileManager::WriteGameData(const char * filename, _GameData & data)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "wb");
	if (file == NULL)
		return false;
	fwrite(&data, sizeof(_GameData), 1, file);
	fclose(file);
	return true;
};
bool FileManager::ReadGameData(const char * filename, _GameData & data)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");
	if (file == NULL)
		return false;
	fread(&data, sizeof(_GameData), 1, file);
	fclose(file);
	return true;
};
