#include "Level.h"
#include "Locator.h"
#include "Graphics.h"
Level::Level(Camera & cam)
	:m_cam(cam)
{
}

void Level::Initialize(std::string  mapFilename,Player* p)
{
	assert(p);
	FileManager::ReadLevelData(mapFilename.c_str(), m_currentLevelData);
	Tile::SetDimensions(m_currentLevelData.tileDimensions.x, m_currentLevelData.tileDimensions.y);
	SpriteSheet* image = Locator::ImageManager()->GetImage("level1");
	Tile::SetImage(image->GetTexture());
	m_tiles.resize(m_currentLevelData.rowsColumns.x * m_currentLevelData.rowsColumns.y);
	Vec2f startPos = { 0.0f,0.0f };
	bool passable = false;
	m_cam.ConfineToMap(RectF(0.0f, 0.0f,
		(float)(m_currentLevelData.tileDimensions.x * m_currentLevelData.rowsColumns.x),
		(float)(m_currentLevelData.tileDimensions.y * m_currentLevelData.rowsColumns.y)));
	int clipIndex = 0;
	p->UpdatePosition(m_currentLevelData.playerPos);
	m_cam.UpdatePosition(m_currentLevelData.playerPos);
	for (int r = 0; r < m_currentLevelData.rowsColumns.y; r++)
	{
		startPos.x = 0.0f;
		for (int c = 0; c < m_currentLevelData.rowsColumns.x; c++)
		{
			bool walkable = true;
			const int index = r * m_currentLevelData.rowsColumns.x + c;
		
			switch (m_currentLevelData.map[r][c])
			{
			case 0:
			{
				clipIndex = m_currentLevelData.levelIndex * image->Columns() + m_currentLevelData.map[r][c];
				passable = false;

			}
			break;
			case 1:
			{
				clipIndex = m_currentLevelData.levelIndex * image->Columns() + m_currentLevelData.map[r][c];
				passable = false;
			}
				break;
			
			case 2:
			{
				clipIndex = m_currentLevelData.levelIndex * image->Columns() + m_currentLevelData.map[r][c];
				passable = false;
				p->CoreData()->position = m_currentLevelData.playerPos;
			

			}
			break;
			case 3:
			{
				clipIndex = m_currentLevelData.levelIndex * image->Columns() + m_currentLevelData.map[r][c];
				passable = false;
				


			}
			break;
			case 4:
			{
				clipIndex = m_currentLevelData.levelIndex * image->Columns() + m_currentLevelData.map[r][c];
				passable = false;
				walkable = false;



			}
			break;
			case 64:
			{
				clipIndex = 63;
				passable = true;

			}
			break;
			case 7:
			{
				clipIndex = m_currentLevelData.levelIndex * image->Columns() + m_currentLevelData.map[r][c];
				passable = true;

			}
			break;
			}
			if (walkable)
			{
				RectF collideRect = { startPos.x,startPos.y,startPos.x + Tile::Width(),startPos.y + (Tile::Height() * 0.5f) };
				m_tiles[index] = std::make_unique<Tile>(startPos,
					Locator::ImageManager()->GetImage("level1")->GetClippedImage(clipIndex), passable,&collideRect);
			}
			else
				m_tiles[index] = std::make_unique<Tile>(startPos,
					Locator::ImageManager()->GetImage("level1")->GetClippedImage(clipIndex), passable);
			startPos.x += Tile::Width();
		}
		startPos.y += Tile::Height();
	}
	
}

void Level::Draw(Graphics& gfx)
{
	Tile* tile = nullptr;
	for (int r = m_startDrawIndex.y; r <= m_endDrawIndex.y; r++)
	{
		for (int c = m_startDrawIndex.x; c <= m_endDrawIndex.x; c++)
		{
			if ((tile = GetTile(r*m_currentLevelData.rowsColumns.x + c)) != nullptr)
				m_cam.Rasterize(tile->GetDrawable());
		}
	}
}

Vec2f Level::InitialPlayerPosition()
{
	return Vec2f();
}

void Level::DoCollision(Entity * ent)
{
	RectF cRect_ent = ent->GetCollisionRect();
	Tile* pTile = nullptr;
	pTile = GetTileCollisionRect(cRect_ent,Vec2i(Sign(ent->GetPosition().x),Sign(ent->GetPosition().y)));
	if(pTile != nullptr)
	{
		RectF tileCollisionRect = pTile->CollisionRect();
		if (cRect_ent.Overlaps(tileCollisionRect))
		{
			CorrectCollision(ent, tileCollisionRect);
			
		}
	}
}

void Level::DoSupported(Entity * ent)
{
	Tile* t;
	t = GetTile(GetIndexOf({ ent->GetCollisionRect().left,ent->GetCollisionRect().bottom }));
	if (!t)return;
	if (!t->Passable())return;

	t = GetTile(GetIndexOf({ ent->GetCollisionRect().right,ent->GetCollisionRect().bottom }));
	if (!t)return;
	if (!t->Passable())return;

	EntityStates s = EntityStates::jumping;
	ent->SetState(s);

}

void Level::Update(const float & dt)
{
	m_startDrawIndex = Vec2i(m_cam.GetPosition());
	m_startDrawIndex /= (int)m_currentLevelData.tileDimensions.x;
	Vec2i dims = { Locator::ScreenWidth<int>() , Locator::ScreenHeight<int>() };
	dims /= (int)m_currentLevelData.tileDimensions.x;
	m_endDrawIndex = m_startDrawIndex + Vec2i(dims.x + 1, dims.y + 1);
}

int Level::CurrentLevelIndex()
{
	return m_currentLevelData.levelIndex;
}

void Level::CorrectCollision(Entity * ent, RectF tile_Rect)
{
	Vec2i vel = Vec2i(Sign((int)ent->CoreData()->velocity.x), Sign((int)ent->CoreData()->velocity.y));
	RectF ent_Rect = ent->GetCollisionRect();
	float px, py;
	ent->CoreData()->boosting = false;
	if (vel.x > 0 && vel.y > 0)
	{
		px = ent_Rect.right - tile_Rect.left;
		py = ent_Rect.bottom - tile_Rect.top;
		if (ent->CoreData()->velocity.y * px > ent->CoreData()->velocity.x * py)
		{
			ent->CoreData()->position.y -= py;
			ent->CoreData()->velocity.y = 0.0f;
			
			ent->SetState( EntityStates::idle);
		}
		else
		{
			ent->CoreData()->position.x -= px;
			ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x )* 0.5f;
			ent->CoreData()->direction.Set(MOVE_LEFT);
		}
		return;
	}
	if (vel.x > 0 && vel.y <= 0)
	{
		px = ent_Rect.right - tile_Rect.left;
		py = tile_Rect.bottom - ent_Rect.top;
		if ((-ent->CoreData()->velocity.y) * px > ent->CoreData()->velocity.x * py)
		{
			ent->CoreData()->position.y += py;
			ent->CoreData()->velocity.y = 0.0f;
			
		}
		else
		{
			ent->CoreData()->position.x -= px;
			ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x )* 0.5f;
			ent->CoreData()->direction.Set(MOVE_LEFT);
			
			
		}
		return;
	}

	if (vel.x <= 0 && vel.y > 0)
	{
		px = tile_Rect.right - ent_Rect.left;
		py = ent_Rect.bottom - tile_Rect.top;
		if (ent->CoreData()->velocity.y * px > (-ent->CoreData()->velocity.x) * py)
		{
			ent->CoreData()->position.y -= py;
			ent->CoreData()->velocity.y = 0.0f;
			ent->SetState(EntityStates::idle);
		}
		else
		{
			ent->CoreData()->position.x += px;
			ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x )* 0.5f;
			ent->CoreData()->direction.Set(MOVE_RIGHT);
			
		}
		return;
	}
	if (vel.x <= 0 && vel.y <= 0)
	{
		px = tile_Rect.right - ent_Rect.left;;
		py = tile_Rect.bottom - ent_Rect.top;
		if ((-ent->CoreData()->velocity.y) * px > (-ent->CoreData()->velocity.x) * py)
		{
			ent->CoreData()->position.y += py;
			ent->CoreData()->velocity.y = 0.0f;
			

		}
		else
		{
			ent->CoreData()->position.x += px;
			ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x) * 0.5f;
			ent->CoreData()->direction.Set(MOVE_RIGHT);
			
		}
		return;
	}
	
}

Tile * Level::GetTileVertical(const int& index, const int& dir)
{
	return GetTile(index + (m_currentLevelData.rowsColumns.y * dir));
}

Tile * Level::GetTileHorizontal(const int & index, const int & dir)
{
	return GetTile(index + dir);
}

Tile * Level::GetTileDiagonal(const int & index, const int & dirX, const int & dirY)
{
	return GetTile(index + (m_currentLevelData.rowsColumns.y * dirY) + dirX);
}

Tile * Level::GetTile(const int & index)
{
	if (index < 0 || index >= m_tiles.size())
		return nullptr;
	return m_tiles[index].get();
}

int Level::GetIndexOf(Vec2f point)
{
	int r = (int)(point.y / m_currentLevelData.tileDimensions.y);
	int c = (int)(point.x / m_currentLevelData.tileDimensions.x);
	return r * m_currentLevelData.rowsColumns.x + c;
}

Tile* Level::GetTileCollisionRect(RectF & ent_Rect,Vec2i& vel)
{
	Vec2i XPos, YPos;
	RectI rect;
	GetTileIndexBias(rect, ent_Rect);
	if (vel.x > 0 && vel.y > 0)
	{
		for (int iy = rect.bottom, iyEnd = rect.top;
			iy >= iyEnd; iy--)
		{
			for (int ix = rect.left, ixEnd = rect.right;
				ix <= ixEnd; ix++)
			{
				int index = iy*m_currentLevelData.rowsColumns.x + ix;

				Tile* t;
				if ((t = GetTile(index)) == nullptr)
					continue;
				if (!t->Passable())
				{
					return t;
				}

			}
		}
	}
	if (vel.x > 0 && vel.y <= 0)
	{
		for (int iy = rect.top, iyEnd = rect.bottom;
			iy <= iyEnd; iy++)
		{
			for (int ix = rect.left, ixEnd = rect.right;
				ix <= ixEnd; ix++)
			{
				int index = iy*m_currentLevelData.rowsColumns.x + ix;

				Tile* t;
				if ((t = GetTile(index)) == nullptr)
					continue;
				if (!t->Passable())
				{
					return t;
				}

			}
		}
	}


	if (vel.x < 0 && vel.y > 0)
	{
		for (int iy = rect.bottom, iyEnd = rect.top;
			iy >= iyEnd; iy--)
		{
			for (int ix = rect.right, ixEnd = rect.left;
				ix >= ixEnd; ix--)
			{
				int index = iy*m_currentLevelData.rowsColumns.x + ix;

				Tile* t;
				if ((t = GetTile(index)) == nullptr)
					continue;
				if (!t->Passable())
				{
					return t;
				}

			}
		}
	}
	if (vel.x <= 0 && vel.y <= 0)
	{
		for (int iy = rect.top, iyEnd = rect.bottom;
			iy <= iyEnd; iy++)
		{
			for (int ix = rect.right, ixEnd = rect.left;
				ix >= ixEnd; ix--)
			{
				int index = iy*m_currentLevelData.rowsColumns.x + ix;

				Tile* t;
				if ((t = GetTile(index)) == nullptr)
					continue;
				if (!t->Passable())
				{
					return t;
				}

			}
		}
	}
	return nullptr;
}

void Level::GetTileIndexBias(RectI& out_rect, const RectF & rect)
{
	
		out_rect.top = GetIndexBiasBottom(rect.top);
		out_rect.bottom = GetIndexBiasTop(rect.bottom);

		out_rect.left = GetIndexBiasRight(rect.left);
		out_rect.right = GetIndexBiasLeft(rect.right);
	
}


