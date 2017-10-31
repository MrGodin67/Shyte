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
	FileManager::ReadLevelData(mapFilename.c_str(), levelData);
	Tile::SetDimensions(levelData.tileDimensions.x, levelData.tileDimensions.y);
	Tile::SetImage(Locator::ImageManager()->GetImage("level1")->GetTexture());
	m_tiles.resize(levelData.rowsColumns.x * levelData.rowsColumns.y);
	Vec2f startPos = { 0.0f,0.0f };
	bool passable = false;
	int clipIndex = 0;
	for (int r = 0; r < levelData.rowsColumns.y; r++)
	{
		startPos.x = 0.0f;
		for (int c = 0; c < levelData.rowsColumns.x; c++)
		{
			
			const int index = r * levelData.rowsColumns.x + c;
		
			switch (levelData.map[r][c])
			{
			case 1:
			{
				clipIndex = 1;
				passable = true;
			}
				break;
			case 0:
			{
				clipIndex = 0;
				passable = false;
				
			}
				break;
			case 2:
			{
				clipIndex = 1;
				passable = true;
				p->SetPosition(levelData.playerPos);
			

			}
			break;
			case 3:
			{
				clipIndex = 2;
				passable = false;
				


			}
			break;
			case 4:
			{
				clipIndex = 4;
				passable = true;



			}
			break;
			}
			m_tiles[index] = std::make_unique<Tile>(startPos,
				Locator::ImageManager()->GetImage("level1")->GetClippedImage(clipIndex), passable);
			startPos.x += Tile::Width();
		}
		startPos.y += Tile::Height();
	}
	
}

void Level::Draw(Graphics& gfx)
{
	for (auto& it : m_tiles)
		m_cam.Rasterize(it->GetDrawable());

	for (auto& it : collisionTiles)
	{
		RectF rect = it->GetRenderDesc().drawRect;
		
		float x = rect.left + -m_cam.GetPos().x;
		float y = rect.top + -m_cam.GetPos().y;
		rect =  RectF(x, y, x + rect.GetWidth(), y + rect.GetHeight());
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), rect.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));

	}
}

Vec2f Level::InitialPlayerPosition()
{
	return Vec2f();
}

void Level::DoCollision(Entity * ent)
{
	RectF cRect_ent = ent->GetCollisionRect();
	collisionTiles.clear();
	RectF rect;
	while (GetTileCollisionRect(cRect_ent, rect))
	{
		if (cRect_ent.Overlaps(rect))
		{
			CorrectCollision(ent, rect);
			break;
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



void Level::CorrectCollision(Entity * ent, RectF tile_Rect)
{
	Vec2i vel = Vec2f(Sign((int)ent->MoveData()->velocity.x), Sign((int)ent->MoveData()->velocity.y));
	RectF ent_Rect = ent->GetCollisionRect();
	Vec2f pos = ent->GetPosition();
	EntityStates states;
	float px, py;

	if (vel.x > 0 && vel.y > 0)
	{
		px = ent_Rect.right - tile_Rect.left;
		py = ent_Rect.bottom - tile_Rect.top;
		if (ent->MoveData()->velocity.y * px > ent->MoveData()->velocity.x * py)
		{
			pos.y -= py;
			ent->MoveData()->velocity.y = 0.0f;
			ent->SetPosition(pos);
			ent->SetState((states = EntityStates::idle));
		}
		else
		{
			pos.x -= px;
			ent->MoveData()->velocity.x = -(ent->MoveData()->velocity.x );
			ent->SetPosition(pos);
			ent->MoveData()->direction.Set(MOVE_LEFT);
		}
		return;
	}
	if (vel.x > 0 && vel.y <= 0)
	{
		px = ent_Rect.right - tile_Rect.left;
		py = tile_Rect.bottom - ent_Rect.top;
		if ((-ent->MoveData()->velocity.y) * px > ent->MoveData()->velocity.x * py)
		{
			pos.y += py;
			ent->MoveData()->velocity.y = 0.0f;
			ent->SetPosition(pos);
		}
		else
		{
			pos.x -= px;
			ent->MoveData()->velocity.x = -(ent->MoveData()->velocity.x );
			ent->SetPosition(pos);
			ent->MoveData()->direction.Set(MOVE_LEFT);
			if (vel.y == 0)
				ent->SetState((states = EntityStates::idle));
			
		}
		return;
	}

	if (vel.x <= 0 && vel.y > 0)
	{
		px = tile_Rect.right - ent_Rect.left;
		py = ent_Rect.bottom - tile_Rect.top;
		if (ent->MoveData()->velocity.y * px > (-ent->MoveData()->velocity.x) * py)
		{
			pos.y -= py;
			ent->MoveData()->velocity.y = 0.0f;
			ent->SetPosition(pos);
			ent->SetState((states = EntityStates::idle));
		}
		else
		{
			pos.x += px;
			ent->MoveData()->velocity.x = -(ent->MoveData()->velocity.x );

			ent->SetPosition(pos);
			ent->MoveData()->direction.Set(MOVE_RIGHT);
			
		}
		return;
	}
	if (vel.x <= 0 && vel.y <= 0)
	{
		px = tile_Rect.right - ent_Rect.left;;
		py = tile_Rect.bottom - ent_Rect.top;
		if ((-ent->MoveData()->velocity.y) * px > (-ent->MoveData()->velocity.x) * py)
		{
			pos.y += py;
			ent->MoveData()->velocity.y = 0.0f;
			ent->SetPosition(pos);
		}
		else
		{
			pos.x += px;
			ent->MoveData()->velocity.x = -(ent->MoveData()->velocity.x);
			ent->SetPosition(pos);
			ent->MoveData()->direction.Set(MOVE_RIGHT);
			if(vel.y == 0)
				ent->SetState((states = EntityStates::idle));
		}
		return;
	}
	
}

Tile * Level::GetTileVertical(const int& index, const int& dir)
{
	int i = index + (levelData.rowsColumns.x * dir);
	if (i < 0 || i >= m_tiles.size())
		return nullptr;
	return m_tiles[i].get();
}

Tile * Level::GetTileHorizontal(const int & index, const int & dir)
{
	int i = index + dir;
	if (i < 0 || i >= m_tiles.size())
		return nullptr;
	return m_tiles[i].get();
}

Tile * Level::GetTileDiagonal(const int & index, const int & dirX, const int & dirY)
{
	int i = index + (levelData.rowsColumns.x * dirY)+dirX;
	if (i < 0 || i >= m_tiles.size())
		return nullptr;
	return m_tiles[i].get();
}

Tile * Level::GetTile(const int & index)
{
	if (index < 0 || index >= m_tiles.size())
		return nullptr;
	return m_tiles[index].get();
}

int Level::GetIndexOf(Vec2f point)
{
	int r = (int)(point.y / levelData.tileDimensions.y);
	int c = (int)(point.x / levelData.tileDimensions.x);
	return r * levelData.rowsColumns.x + c;
}

bool Level::GetTileCollisionRect(RectF & ent_Rect, RectF & out_rect)
{
	Vec2i XPos, YPos;
	RectI rect;
	GetTileIndexBias(rect, ent_Rect);
	for (int iy = rect.top, iyEnd = rect.bottom;
		iy <= iyEnd; iy++)
	{
		for (int ix = rect.left, ixEnd = rect.right;
			ix <= ixEnd; ix++)
		{
			int index = iy*levelData.rowsColumns.x + ix;
			
			Tile* t = GetTile(index);
			if (!t)continue;
			collisionTiles.push_back(t);
			if (!t->Passable())
			{
				out_rect = t->GetRenderDesc().drawRect;
				return true;
			}
			
		}
	}
	return false;
}


void Level::GetTileIndexBias(RectI& out_rect, const RectF & rect)
{
	out_rect.top    = GetIndexBiasBottom(rect.top);
	out_rect.bottom = GetIndexBiasTop(rect.bottom);

	out_rect.left  = GetIndexBiasRight(rect.left);
	out_rect.right = GetIndexBiasLeft(rect.right);
}