#pragma once
#include "Tile.h"
#include "StringHandler.h"
#include "Player.h"
#include "Camera.h"
#include "FileManager.h"
class Level
{
private:
	std::vector<std::unique_ptr<Tile>> m_tiles;
	Camera& m_cam;
	_LevelFileData levelData;
	std::vector<Tile*> collisionTiles;
	std::vector<Tile*> m_renderTiles;
	void CorrectCollision(Entity* ent, RectF tile_Rect);
	Tile* GetTileVertical(const int& index,const int& dir);
	Tile* GetTileHorizontal (const int& index, const int& dir);
	Tile* GetTileDiagonal(const int& index, const int& dirX, const int& dirY);
	Tile* GetTile(const int& index);
	int GetIndexOf(Vec2f point);
	int GetIndexBiasRight(float x)
	{
		return (int)(x / levelData.tileDimensions.x);
	};
	int GetIndexBiasBottom(float y)
	{
		return (int)(y / levelData.tileDimensions.y);
	};
	int GetIndexBiasLeft(float x)
	{
		int ix = (int)(x / levelData.tileDimensions.x);
		if ((float)ix * levelData.tileDimensions.x == x)
		{
			ix--;
		}
		return ix;
	};
	int GetIndexBiasTop(float y)
	{
		int iy = (int)(y / levelData.tileDimensions.y);
		if ((float)iy * levelData.tileDimensions.y == y)
		{
			iy--;
		}
		return iy;
	};
	bool GetTileCollisionRect(RectF& ent_Rect, RectF& out_rect);
	void GetTileIndexBias(RectI& out_rect, const RectF& rect);
	void GetRenderTiles();
public:
	Level() = default;
	Level(Camera& cam);
	~Level() {}
	void Initialize(std::string mapFilename,Player* p);
	void Draw(class Graphics& gfx);
	Vec2f InitialPlayerPosition();
	void DoCollision(Entity* ent);
	void DoSupported(Entity* ent);
	void Update(const float& dt);
	
};