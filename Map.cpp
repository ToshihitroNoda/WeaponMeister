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

// 指定された座標（ワールド座標）の地形データを取得する。
int Map::GetTerrain(float worldX, float worldY, float worldZ)
{
	if (worldZ != -10000.0) worldY = worldZ; //★【YとZを変換】Zの入力があるときはZをYとして扱う
	// 負の座標が指定された場合は、何も無いものとして扱う
	if (worldX < 0 || worldY < 0)
		return None;

	// マップ座標系（二次元配列の行と列）に変換する
	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	// 二次元配列の範囲外は、何も無いものとして扱う
	if (mapX >= terrain.Width || mapY >= terrain.Height)
		return None;

	return terrain[mapY][mapX]; // 二次元配列から地形IDを取り出して返却する
}

int Map::GetObjects(float worldX, float worldY, float worldZ)
{
	if (worldZ != -10000.0) worldY = worldZ; //★【YとZを変換】Zの入力があるときはZをYとして扱う
	// 負の座標が指定された場合は、何も無いものとして扱う
	if (worldX < 0 || worldY < 0)
		return None;

	// マップ座標系（二次元配列の行と列）に変換する
	int mapX = (int)(worldX / CellSize);
	int mapY = (int)(worldY / CellSize);

	// 二次元配列の範囲外は、何も無いものとして扱う
	if (mapX >= objects.Width || mapY >= objects.Height)
		return None;

	return objects[mapY][mapX]; // 二次元配列から地形IDを取り出して返却する
}

// ゲームオブジェクト描画
void Map::DrawObjects()
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
void Map::DrawTerrain()
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
				if (id == terrain_sand)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Sand"));
				}
				if (id == terrain_stone)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Stone"));
				}
				if (id == terrain_volcano)
				{
					gm.mapTerrain.push_back(std::make_shared<MapTerrain>(x, -25, y, "Volcano"));
				}
			}
		}
		terrainLoad = true;
	}
}

// 指定された座標（ワールド座標）の地形が壁か調べる
bool Map::IsWall(float worldX, float worldY, float worldZ)
{
	int objectsID = GetObjects(worldX, worldY, worldZ); // 指定された座標の地形のIDを取得

	return IsWall(objectsID);
}

//あるIDが壁かどうかだけ調べる
bool Map::IsWall(int objectsID)
{
	for (int i = 0; i < sizeof(NotWallNums) / sizeof(NotWallNums[0]); i++)//[配列の数を求めるには]https://qiita.com/yohhoy/items/a2ab2900a2bd36c31879
	{   // 壁じゃない番号のとき
		if (objectsID == NotWallNums[i]) return false;
	}
	//SetTerrain(worldX, worldY, worldZ);
	//if (terrainID == 0) { printfDx("%d ", terrainID); printfDx("(%f %f)", worldX, worldZ); count++; }
	return (objectsID != -1);// (terrainID == Wall); // 地形が壁ならtrue、違うならfalseを返却する
}
