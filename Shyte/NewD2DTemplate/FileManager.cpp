#include "FileManager.h"
#include "Player.h"
void FileManager::WriteLevelData(const char * filename, _LevelFileData & data)

{
	FILE* file = nullptr;
	fopen_s(&file, filename, "wb");
	assert(file);
	fwrite(&data, sizeof(_LevelFileData), 1, file);
	fclose(file);
}
void FileManager::ReadLevelData(const char * filename, _LevelFileData & data)

{
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");
	assert(file);
	fread(&data, sizeof(_LevelFileData), 1, file);
	fclose(file);
}
void FileManager::WritePlayerData(const char * filename, MainPlayerData & data)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "wb");
	assert(file);
	fwrite(&data, sizeof(MainPlayerData), 1, file);
	fclose(file);
}
void FileManager::ReadPlayerData(const char * filename, MainPlayerData & data)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");
	assert(file);
	fread(&data, sizeof(MainPlayerData), 1, file);
	fclose(file);
}
void FileManager::WriteGameData(const char * filename, _GameData & data)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "wb");
	assert(file);
	fwrite(&data, sizeof(_GameData), 1, file);
	fclose(file);
};
void FileManager::ReadGameData(const char * filename, _GameData & data)
{
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");
	assert(file);
	fread(&data, sizeof(_GameData), 1, file);
	fclose(file);
}
;
