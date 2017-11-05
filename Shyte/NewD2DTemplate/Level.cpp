#include "Level.h"
#include "Locator.h"
#include "Graphics.h"
Level::Level(Camera & cam,Player& player)
	:m_cam(cam),m_player(player)
{
}

void Level::Initialize(std::string  mapFilename)
{
	
	m_healthMeter = std::make_unique<Meter>(m_player.CoreData()->max_hitpoints, RectF(30.0f, 30.0f, 200.0f, 45.0f),
		RectF(1.0f, 0.0f, 0.0f, 1.0f), RectF(0.0f, 1.0f, 0.0f, 0.5f),
		RectF(1.0f, 1.0f, 1.0f, 1.0f), "Tahoma12");
	std::string str = "Health";
	m_healthMeter->SetCaption(str);
	{
		
		m_expMeter = std::make_unique<Meter>(m_player.CoreData()->max_hitpoints, RectF(220.0f, 30.0f, 300.0f, 45.0f),
			RectF(1.0f, 0.0f, 0.0f, 1.0f), RectF(0.0f, 1.0f, 0.0f, 0.5f),
			RectF(1.0f, 1.0f, 1.0f, 1.0f), "Tahoma12");
		std::string str = "Experience Level [ "+std::to_string(m_player.CoreData()->exp_level) +" ]";
		m_expMeter->SetCaption(str);
	}
	
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
	m_player.UpdatePosition(m_currentLevelData.playerPos);
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
			case 7:// exit point
			{
				clipIndex = m_currentLevelData.levelIndex * image->Columns() + m_currentLevelData.map[r][c];
				passable = true;
				m_exitRect = { m_currentLevelData.exitPos.x,m_currentLevelData.exitPos.y,
				m_currentLevelData.exitPos.x + Tile::Width() ,m_currentLevelData.exitPos.y + Tile::Height() };
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
	//loop through visible tiles
	for (int r = m_startDrawIndex.y; r <= m_endDrawIndex.y; r++)
	{
		for (int c = m_startDrawIndex.x; c <= m_endDrawIndex.x; c++)
		{
			if ((tile = GetTile(r*m_currentLevelData.rowsColumns.x + c)) != nullptr)
				m_cam.Rasterize(tile->GetDrawable());
		}
	}
	gfx.GetD2DLayerViewPort()->Rasterize(m_healthMeter->GetDrawable());
	gfx.GetD2DLayerViewPort()->Rasterize(m_expMeter->GetDrawable());
	

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
	if ((t = GetTile(GetIndexOf({ ent->GetCollisionRect().left,ent->GetCollisionRect().bottom }))) == nullptr)
		return;
	if (!t->Passable())return;

	if ((t = GetTile(GetIndexOf({ ent->GetCollisionRect().right,ent->GetCollisionRect().bottom }))) == nullptr)
		return;
	if (!t->Passable())return;

	
	ent->SetState(EntityStates::jumping);

}

bool Level::Update(const float & dt)
{
	// get index range for drawing visible tiles
	DoCollision(&m_player);
	DoSupported(&m_player);
	m_player.Update(dt);
	static float inc = 0.0f;
	inc += dt;
	if ((inc += dt) > 1.0f)
	{
		m_player.CoreData()->exp_points++;
		inc = 0.0f;
		if (m_player.CoreData()->exp_points >= 100)
		{
			m_player.CoreData()->exp_level++;
			m_player.CoreData()->exp_points = 0;
			std::string str = "Experience Level [ " + std::to_string(m_player.CoreData()->exp_level) + " ]";
			m_expMeter->SetCaption(str);
		}
	}
	m_healthMeter->Update((int)m_player.CoreData()->hit_points);
	m_expMeter->Update(m_player.CoreData()->exp_points);
	m_startDrawIndex = Vec2i(m_cam.GetPosition());
	m_startDrawIndex /= (int)m_currentLevelData.tileDimensions.x;
	Vec2i dims = { Locator::ScreenWidth<int>() , Locator::ScreenHeight<int>() };
	dims /= (int)m_currentLevelData.tileDimensions.x;
	m_endDrawIndex = m_startDrawIndex + Vec2i(dims.x + 1, dims.y + 1);
	if (m_exitRect.Contains(m_player.GetCenter()))
	{
		m_player.CoreData()->level_index++;
		if (m_player.CoreData()->level_index >= m_maxLevels)
			m_player.CoreData()->level_index = 0;
		return false;
	}
	return true;
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
			if(ent->Type() == _EntityType::player)
			   ent->SetState( EntityStates::idle);
		}
		else
		{
			if (ent->Type() == _EntityType::player)
			{
				if (abs(ent->CoreData()->velocity.x) > 50.0f)
					ent->CoreData()->hit_points--;
			}
			ent->CoreData()->position.x -= px;
			ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x )* 0.5f;
			ent->CoreData()->direction.Set(MOVE_LEFT);
			
		}
		ent->UpdatePosition(ent->CoreData()->position);
		return;
	}
	if (vel.x > 0 && vel.y <= 0)
	{
		px = ent_Rect.right - tile_Rect.left;
		py = tile_Rect.bottom - ent_Rect.top;
		if ((-ent->CoreData()->velocity.y) * px > ent->CoreData()->velocity.x * py)
		{
			if (ent->Type() == _EntityType::player)
			{
				if (abs(ent->CoreData()->velocity.y) > 50.0f)
					ent->CoreData()->hit_points--;
			}
			ent->CoreData()->position.y += py;
			ent->CoreData()->velocity.y = 0.0f;
			
			
		}
		else
		{
			if (ent->Type() == _EntityType::player)
			{
				if (abs(ent->CoreData()->velocity.x) > 50.0f)
					ent->CoreData()->hit_points--;
			}
			ent->CoreData()->position.x -= px;
			ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x )* 0.5f;
			ent->CoreData()->direction.Set(MOVE_LEFT);
			
			
		}
		ent->UpdatePosition(ent->CoreData()->position);
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
			if (ent->Type() == _EntityType::player)
			    ent->SetState(EntityStates::idle);
		}
		else
		{
			if (ent->Type() == _EntityType::player)
			{
				if (abs(ent->CoreData()->velocity.x) > 50.0f)
					ent->CoreData()->hit_points--;
			}
			ent->CoreData()->position.x += px;
			ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x )* 0.5f;
			ent->CoreData()->direction.Set(MOVE_RIGHT);
			
			
		}
		ent->UpdatePosition(ent->CoreData()->position);
		return;
	}
	if (vel.x <= 0 && vel.y <= 0)
	{
		px = tile_Rect.right - ent_Rect.left;;
		py = tile_Rect.bottom - ent_Rect.top;
		if ((-ent->CoreData()->velocity.y) * px > (-ent->CoreData()->velocity.x) * py)
		{
			if (ent->Type() == _EntityType::player)
			{
				if (abs(ent->CoreData()->velocity.y) > 50.0f)
					ent->CoreData()->hit_points--;
			}
			ent->CoreData()->position.y += py;
			ent->CoreData()->velocity.y = 0.0f;
			

		}
		else
		{
			if (ent->Type() == _EntityType::player)
			{
				if (abs(ent->CoreData()->velocity.x) > 50.0f)
					ent->CoreData()->hit_points--;
			}
			ent->CoreData()->position.x += px;
			ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x) * 0.5f;
			ent->CoreData()->direction.Set(MOVE_RIGHT);
			
			
		}
		ent->UpdatePosition(ent->CoreData()->position);
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


