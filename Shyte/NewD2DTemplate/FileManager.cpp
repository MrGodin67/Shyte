#include "FileManager.h"

void FileManager::WriteLevelData(const char * filename, _LevelFileData & data)

{
	FILE* file;
	fopen_s(&file, filename, "wb");
	assert(file);
	fwrite(&data, sizeof(_LevelFileData), 1, file);
	fclose(file);
}
void FileManager::ReadLevelData(const char * filename, _LevelFileData & data)

{
	FILE* file;
	fopen_s(&file, filename, "rb");
	assert(file);
	fread(&data, sizeof(_LevelFileData), 1, file);
	fclose(file);
};
