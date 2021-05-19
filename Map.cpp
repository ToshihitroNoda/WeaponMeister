#include "Map.h"

// 敵出現射程の辞書初期化【先に計算して辞書化】すると計算が必要なくなり【高速化する】
	//【注意！XとYの単位はマス目】
void Map::InitSpawnDic(int rangeCellX, int rangeCellY)
{
	SpawnDic.clear();//一旦辞書をクリアするのでゲーム中の再設定も可(だが処理時間はかかる)
	// 敵出現射程の辞書初期化
	// ★ X = A cosθ Y = B sinθ(←楕円の方程式)
	// ★ 楕円の半径 r = √(A×A×cosθ×cosθ + B×B×sinθ×sinθ)
	// ★ xの2乗 + yの2乗 < rならば楕円の内側
	float A2 = (float)(rangeCellX * rangeCellX); // 2乗
	float B2 = (float)(rangeCellY * rangeCellY); // 2乗
	for (int x = -rangeCellX; x <= rangeCellX; x++)
	{
		for (int y = -rangeCellY; y <= rangeCellY; y++)
		{   //★[逆三角関数] https://cpprefjp.github.io/reference/cmath/atan2.html
			float theta = (float)std::atan2(y, x); // ★[逆三角関数]
			float cos_t = std::cos(theta);
			float sin_t = std::sin(theta);
			float r2 = A2 * cos_t * cos_t + B2 * sin_t * sin_t;
			if (x * x + y * y <= r2) // ★ xの2乗 + yの2乗 < rならば楕円の内側
			{   //楕円の内側なら辞書SpawnDic[(x,y)] = true;として登録
				//【★楕円にしたいときはこちら】SpawnDic[CellXY(x,y)] = true; //【例】SpawnDic[(3,2)] = true;
			}
			//【★四角形にしたいときはこちら】
			SpawnDic[CellXY(x, y)] = true;
		}
	}
}

// ゲームオブジェクト描画
void Map::LoadObjects()
{
	if (!objectsLoad)
	{
		for (int cellX = 0; cellX < terrain.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain.Height; cellY++)
			{
				float x = (float)(cellX * CellSize) + rotaGraphShiftX; //マス目サイズ/2ずらし
				float y = (float)(cellY * CellSize) + rotaGraphShiftY; //マス目サイズ/2ずらし
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

//★地形を描く3D対応でY平面に描く
void Map::LoadTerrain()
{
	if (!terrainLoad)
	{
		for (int cellX = 0; cellX < terrain.Width; cellX++)
		{
			for (int cellY = 0; cellY < terrain.Height; cellY++)
			{
				float x = (float)(cellX * CellSize) + rotaGraphShiftX; //マス目サイズ/2ずらし
				float y = (float)(cellY * CellSize) + rotaGraphShiftY; //マス目サイズ/2ずらし
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
