#include "Level.h"
#include "Locator.h"
#include "Graphics.h"
#include "Mushroom.h"
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
	m_player.SetPosition(m_currentLevelData.playerPos);
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
			case 8:// mushroom
			{
				m_enemies.push_back(std::make_unique<Mushroom>(InitialPlayerCoreData::Get("mushroom")));
				m_enemies.back()->SetPosition(startPos);
				clipIndex = 63;
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
	GetCollisionRects();
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
	for (auto& it : m_enemies)
		m_cam.Rasterize(it->GetDrawable());

	float inc = 1.0f / (float)m_verticalLines.size();
	float counter = 0.0f;
	
	
	

	for (auto& it : m_collisionRects)
	{
		RectF r = it;
		r.Translate(-m_cam.GetPosition().x, -m_cam.GetPosition().y);
		gfx.DrawRectangle(D2D1::Matrix3x2F::Identity(), r.ToD2D(), D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));

	}
	
}

Vec2f Level::InitialPlayerPosition()
{
	return Vec2f();
}

void Level::DoCollision(Entity * ent)
{
	
	
	
	/*Tile* pTile = nullptr;
	pTile = GetTileCollisionRect(cRect_ent,Vec2i(Sign(ent->GetPosition().x),Sign(ent->GetPosition().y)));
	if(pTile != nullptr)
	{

	    RectF tileCollisionRect = pTile->CollisionRect();
		if (cRect_ent.Overlaps(tileCollisionRect))
		{
			CorrectCollision(ent, tileCollisionRect);

		}
	}*/
	for (auto& it : m_collisionRectsInView)
	{
		Vec2f correction;
		RectF cRect_ent = m_player.GetCollisionRect();
		
		if (Intersect::BoundingBox(cRect_ent, it, correction))
		{
			
			Vec2f player_pos = m_player.GetPosition();
			Vec2f player_vel = m_player.GetVelocity();
			Vec2i dir(Sign<int>(player_vel.x), Sign<int>(player_vel.y));
			if (correction.x > correction.y)
			{
				player_pos.y += (-dir.y * correction.y);
				player_vel.y = 0.0f;
				m_player.SetPosition(player_pos);
				m_player.SetVelocity(player_vel);
				if (m_player.Type() == _EntityType::player)
				{
					dir.y > 0 ? m_player.SetState(EntityStates::idle) : m_player.SetState(EntityStates::jumping);
				}
				

			}
			else if(correction.x < correction.y)
			{
				
				player_pos.x += (-dir.x * correction.x);
				player_vel.x = -player_vel.x;
				m_player.SetPosition(player_pos);
				m_player.SetVelocity(player_vel);
				m_player.CoreData()->direction.Set(-dir.x);
			}
			
		}
	}
	
	/*for (auto& it : m_collisionRectsInView)
	{
		if (cRect_ent.Overlaps(it))
		{
			CorrectCollision(ent, it);
			break;
		}
	}*/
	
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
	GetCollisionRectsInView(m_player.GetCenter());
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
	for (auto& it : m_enemies)
	{
		DoCollision(it.get());
		ConfineToPlatform(it.get());
		it->Update(dt);
	}
	return true;
}

int Level::CurrentLevelIndex()
{
	return m_currentLevelData.levelIndex;
}

void Level::ConfineToPlatform(Entity * ent)
{
	int i =GetIndexOf(ent->GetPosition());
	Tile* t = GetTileDiagonal(GetIndexOf(ent->GetPosition()), Sign(ent->CoreData()->velocity.x),1);
	if (t)
	{
		if (t->Passable())
		{
			RectF tRect = t->CollisionRect();
			RectF cRect = ent->GetCollisionRect();
			if (Sign(ent->CoreData()->velocity.x) > 0)
			{
				if (abs(tRect.left - cRect.right) < 10.0f)
				{
					ent->CoreData()->direction.Set(-(Sign(ent->CoreData()->velocity.x)));
					ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x);

				}
			}
			else
			{
				if (cRect.left - tRect.right < 10.0f)
				{
					ent->CoreData()->direction.Set(-(Sign(ent->CoreData()->velocity.x)));
					ent->CoreData()->velocity.x = -(ent->CoreData()->velocity.x);

				}
			}
		}
	}
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
			else
				ent->SetState(EntityStates::moving);
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
			else
				ent->SetState(EntityStates::moving);
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
		
		return;
	}
	
}

void Level::GetCollisionRects()
{
	for (int r = 0; r < m_currentLevelData.rowsColumns.y; r++)
	{
		RectF rect;
		for (int c = 0; c < m_currentLevelData.rowsColumns.x; c++)
		{
			const int index = r *m_currentLevelData.rowsColumns.x + c;
			Tile* t = GetTile(index);
			if (t)
			{
				if (!t->Passable())// solid
				{
					rect = t->CollisionRect();
					// pass the column (c) as a reference so SetCollisionRect can iterate through
					// the column and qwhen done, this (c) will be the new value
					SetCollisionRectHorizontal(r, c, rect);
					m_collisionRects.push_back(rect);
					
					
				}
				
			}
		}
	}
	
}



void Level::SetCollisionRectHorizontal(const int & row, int & col, RectF & rect)
{
	
		for ( ;col < m_currentLevelData.rowsColumns.x-1; col++)
		{
			const int index = row *m_currentLevelData.rowsColumns.x + col;
			Tile* t = GetTileHorizontal(index, 1);
			Tile* t2 = GetTile(index);
			if (t)
			{
				if (t->Passable() )
					return;
				else
				{
					if (t2->CollisionRect().GetHeight() > t->CollisionRect().GetHeight())
					{
						rect.right = t2->CollisionRect().right;
						return;
					}
					else
						rect.right = t->CollisionRect().right;
				}
			}

		}
	
}
bool Level::AreRectsTouching(const RectF & A, const RectF & B)
{
	return A.top <= B.bottom && A.bottom >= B.top &&
		A.left <= B.right && A.right >= B.left;
}
void Level::GetCollisionRectsInView(Vec2f& player_pos)
{
	m_collisionRectsInView.clear();
	// camera view frustum
	RectF viewRect = m_cam.GetViewFrame();
	for (auto& it : m_collisionRects)
	{
		// if any are inside the view rectangle
		if (it.Overlaps(viewRect))
			m_collisionRectsInView.push_back(it);
	}
	// sort by closest ? .. works but isn't too efficient
	std::sort(m_collisionRectsInView.begin(), m_collisionRectsInView.end(), [player_pos](RectF& A, RectF& B)
	{
		// center of player to center of rectangle
		Vec2f AC(A.left + A.GetWidth() * 0.5f, A.top + A.GetHeight() * 0.5f);
		Vec2f BC(B.left + B.GetWidth() * 0.5f, B.top + B.GetHeight() * 0.5f);
		return (player_pos - AC).LenSq() < (player_pos - BC).LenSq();
	});

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


