#include "Map.h"

// “GoŒ»Ë’ö‚Ì«‘‰Šú‰»yæ‚ÉŒvZ‚µ‚Ä«‘‰»z‚·‚é‚ÆŒvZ‚ª•K—v‚È‚­‚È‚èy‚‘¬‰»‚·‚éz
	//y’ˆÓIX‚ÆY‚Ì’PˆÊ‚Íƒ}ƒX–Úz
void Map::InitSpawnDic(int rangeCellX, int rangeCellY)
{
	SpawnDic.clear();//ˆê’U«‘‚ğƒNƒŠƒA‚·‚é‚Ì‚ÅƒQ[ƒ€’†‚ÌÄİ’è‚à‰Â(‚¾‚ªˆ—ŠÔ‚Í‚©‚©‚é)
	// “GoŒ»Ë’ö‚Ì«‘‰Šú‰»
	// š X = A cosƒÆ Y = B sinƒÆ(©‘È‰~‚Ì•û’ö®)
	// š ‘È‰~‚Ì”¼Œa r = ã(A~A~cosƒÆ~cosƒÆ + B~B~sinƒÆ~sinƒÆ)
	// š x‚Ì2æ + y‚Ì2æ < r‚È‚ç‚Î‘È‰~‚Ì“à‘¤
	float A2 = (float)(rangeCellX * rangeCellX); // 2æ
	float B2 = (float)(rangeCellY * rangeCellY); // 2æ
	for (int x = -rangeCellX; x <= rangeCellX; x++)
	{
		for (int y = -rangeCellY; y <= rangeCellY; y++)
		{   //š[‹tOŠpŠÖ”] https://cpprefjp.github.io/reference/cmath/atan2.html
			float theta = (float)std::atan2(y, x); // š[‹tOŠpŠÖ”]
			float cos_t = std::cos(theta);
			float sin_t = std::sin(theta);
			float r2 = A2 * cos_t * cos_t + B2 * sin_t * sin_t;
			if (x * x + y * y <= r2) // š x‚Ì2æ + y‚Ì2æ < r‚È‚ç‚Î‘È‰~‚Ì“à‘¤
			{   //‘È‰~‚Ì“à‘¤‚È‚ç«‘SpawnDic[(x,y)] = true;‚Æ‚µ‚Ä“o˜^
				//yš‘È‰~‚É‚µ‚½‚¢‚Æ‚«‚Í‚±‚¿‚çzSpawnDic[CellXY(x,y)] = true; //y—ázSpawnDic[(3,2)] = true;
			}
			//yšlŠpŒ`‚É‚µ‚½‚¢‚Æ‚«‚Í‚±‚¿‚çz
			SpawnDic[CellXY(x, y)] = true;
		}
	}
}

// ƒQ[ƒ€ƒIƒuƒWƒFƒNƒg•`‰æ
void Map::LoadObjects()
{
	if (!objectsLoad)
	{
		for (int cellX = 0; cellX < terrain.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain.Height; cellY++)
			{
				float x = (float)(cellX * CellSize) + rotaGraphShiftX; //ƒ}ƒX–ÚƒTƒCƒY/2‚¸‚ç‚µ
				float y = (float)(cellY * CellSize) + rotaGraphShiftY; //ƒ}ƒX–ÚƒTƒCƒY/2‚¸‚ç‚µ
				int id = -1;
				if (cellY < (int)objects.size()
					&& cellX < (int)objects[cellY].size())
				{
					id = objects[cellY][cellX];
				}
				if (id == Fielditem)
				{
					gm.fieldItems.push_back(std::make_shared<FieldItem>(x, 30, y));
				}
				for (int i = 0; i < ObjectIDs.size(); i++)
				{
					if (id == ObjectIDs[i])
					{
						gm.mapObjects.push_back(std::make_shared<MapObjects>(x, 0, y, ObjectWidths[i], ObjectLengths[i], ObjectNames[i]));
					}
				}
			}
		}
		objectsLoad = true;
	}
}

//š’nŒ`‚ğ•`‚­3D‘Î‰‚ÅY•½–Ê‚É•`‚­
void Map::LoadTerrain()
{
	if (!terrainLoad)
	{
		for (int cellX = 0; cellX < terrain.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain.Height; cellY++)
			{
				float x = (float)(cellX * CellSize) + rotaGraphShiftX; //ƒ}ƒX–ÚƒTƒCƒY/2‚¸‚ç‚µ
				float y = (float)(cellY * CellSize) + rotaGraphShiftY; //ƒ}ƒX–ÚƒTƒCƒY/2‚¸‚ç‚µ
				int id = -1;
				if (cellY < (signed)terrain.size()
					&& cellX < (signed)terrain[cellY].size())
				{
					id = terrain[cellY][cellX];
				}
				if (id == terrain_grass)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Grass"));
				}
				else if (id == terrain_sand)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Sand"));
				}
				else if (id == terrain_stone)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Stone"));
				}
				else if (id == terrain_volcano)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Volcano"));
				}
			}
		}
		terrainLoad = true;
	}
}
