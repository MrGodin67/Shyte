#pragma once
#include "Tile.h"
#include "StringHandler.h"
#include "Player.h"
#include "Camera.h"
#include "FileManager.h"
#include "Meter.h"
#include "Line.h"
#include "Rectangle.h"
struct TileGroup
{
	std::vector<RectF> rects;
};
struct shape
{
	std::vector<Vec2f> vertices;
	std::vector<unsigned int> indices;
};
class Level
{
private:
	std::vector<std::unique_ptr<Tile>> m_tiles;
	std::vector<std::unique_ptr<Entity>> m_enemies;
	std::unique_ptr<Meter> m_healthMeter;
	std::unique_ptr<Meter> m_expMeter;
	std::vector<RectF> m_collisionRects;
	std::vector<RectF> m_collisionRectsInView;
	std::vector<sLine> m_horizontalLines;
	std::vector<sLine> m_verticalLines;

	std::vector<TileGroup> m_tileGroups;
	Camera& m_cam;
	Player& m_player;
	_LevelFileData m_currentLevelData;
	Vec2i m_startDrawIndex;
	Vec2i m_endDrawIndex;
	RectF m_exitRect;
	sLine m_testLine = { Vec2f(72.0f,72.0f),Vec2f(125.0f,600.0f) };
	sRectangle m_testRect = { RectF(100.0f,100.0f,200.0f,200.0f),true,false };
	int m_maxLevels = 3;
	void ConfineToPlatform(Entity* ent);
	void CorrectCollision(Entity* ent, RectF tile_Rect);
	void GetCollisionRects();
	void GetCollisionRectsInView(Vec2f& player_pos);
	void SetCollisionRectHorizontal(const int& row, int& col, RectF& rect);
	bool AreRectsTouching(const RectF& A, const RectF& B);
	Tile* GetTileVertical(const int& index,const int& dir);
	Tile* GetTileHorizontal (const int& index, const int& dir);
	Tile* GetTileDiagonal(const int& index, const int& dirX, const int& dirY);
	Tile* GetTile(const int& index);
	int GetIndexOf(Vec2f point);
	int GetIndexBiasRight(float x)
	{
		return (int)(x / m_currentLevelData.tileDimensions.x);
	};
	int GetIndexBiasBottom(float y)
	{
		return (int)(y / m_currentLevelData.tileDimensions.y);
	};
	int GetIndexBiasLeft(float x)
	{
		int ix = (int)(x / m_currentLevelData.tileDimensions.x);
		if ((float)ix * m_currentLevelData.tileDimensions.x == x)
		{
			ix--;
		}
		return ix;
	};
	int GetIndexBiasTop(float y)
	{
		int iy = (int)(y / m_currentLevelData.tileDimensions.y);
		if ((float)iy * m_currentLevelData.tileDimensions.y == y)
		{
			iy--;
		}
		return iy;
	};
	Tile* GetTileCollisionRect(RectF& ent_Rect,Vec2i& vel);
	void GetTileIndexBias(RectI& out_rect, const RectF& rect);

public:
	Level() = default;
	Level(Camera& cam, Player& player);
	~Level() {}
	void Initialize(std::string mapFilename);
	void Draw(class Graphics& gfx);
	Vec2f InitialPlayerPosition();
	void DoCollision(Entity* ent);
	void DoSupported(Entity* ent);
	bool Update(const float& dt);
	int CurrentLevelIndex();
	Vec2f GetWorldSize() {
		return{ m_currentLevelData.tileDimensions.x * m_currentLevelData.rowsColumns.x,
                m_currentLevelData.tileDimensions.y + m_currentLevelData.rowsColumns.y };
	}
	
};