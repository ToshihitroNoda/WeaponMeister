#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <map>  
#include <memory> 
#include <cmath> 
#include <fstream> 
#include <string> 
#include <sstream> 
#include <assert.h> 

#include "Screen.h"
#include "GameManager.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Image.h"
#include "FieldItem.h"
#include "MapObjects.h"
#include "MapTerrain.h"
#include "DataCsv.h"

// CSVファイルの読込み & 当たり判定可能なマス目
struct CsvCell : public DataCsv
{
	int NoneData	  = -1; // この値のCSVデータはデータがないマスとみなす
	int CellSize	  = 1;
	CsvCell(int CellSize = 1, std::string filePath = "") : DataCsv(filePath)
	{
		assert(CellSize > 0 && "マス目サイズ指定CellSizeは1以上に設定して！" != "");
		this->CellSize = CellSize;
	};
	~CsvCell() { clear(); }; //お掃除処理はこちら
	// csvファイルの読み込み
	void LoadMap(int CellSize, std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadMap(filePath); // ファイル読込み
	}
};

class Map
{
public:
	GameManager& gm = GameManager::GetInstance();

	const int None			  = -1;   // 何も無いマス
	const int terrain_grass   = 0;	  // 草の地面
	const int terrain_sand	  = 1;	  // 砂の地面
	const int terrain_stone   = 2;	  // 石の地面
	const int terrain_volcano = 3;	  // 火山の地面

	const int Fielditem		  = 0;	  // フィールド上のアイテム
	const int Spruce_1		  = 1;    // 木1

	//壁じゃないもの
	int NotWallNums[2] = { -1,0 };

	// マス目のXとYを保持するデータ型
	struct CellXY
	{
		int X = 0;
		int Y = 0;
		CellXY(int X, int Y) : X{ X }, Y{ Y }
		{};
		bool operator < (const CellXY& otherXY) const {
			if (Y < otherXY.Y) return true;		// Y優先並べ替え
			if (Y > otherXY.Y) return false;
			if (X < otherXY.X) return true;		// Yが同じ時はXを比較
			if (X > otherXY.X) return false;
			return false;						// 完全一致のときは
		}
	};

	int SpawnRangeX = 30;		// オブジェクト出現射程スポーンレンジ【注意！Xの単位はマス目】
	int SpawnRangeY = 30;		// オブジェクト出現射程スポーンレンジ【注意！Yの単位はマス目】

	std::map<CellXY, bool> SpawnDic;

	const int CellSize = 32;	// マップの1マスのピクセル数

	bool isRotaGraph = true;	// DrawRotaGraphを使うときはマス目サイズ/2ずらす必要がある

	// 画像の中心を起点に描く場合のずれ
	float rotaGraphShiftX = (isRotaGraph) ? (float)CellSize / 2 : 0.0f;
	float rotaGraphShiftY = (isRotaGraph) ? (float)CellSize / 2 : 0.0f;
	float rotaGraphShiftZ = (isRotaGraph) ? (float)CellSize / 2 : 0.0f;

	CsvCell terrain;			// ★地形データ
	CsvCell objects;			// 敵配置データ

	int TerrainWidth = 0;		// マップデータの横のマス数
	int TerrainHeight = 0;		// マップデータの縦のマス数
	float positionX = 0;		// 現在の位置（マップ左端の座標）
	float positionY = 0;		// 現在の位置（マップ上端の座標）

	bool objectsLoad = false;
	bool terrainLoad = false;

	// コンストラクタ
	// startPosition : 開始位置（デバッグやリスタート時に、面の途中から開始できるように）
	// filePath : CSVファイルのパス
	Map(float startPosition, std::string stageName)
	{
		positionX = startPosition;
		objectsLoad = false;

		objects.LoadMap(CellSize, "Resource/Map/" + stageName + "_objects.csv");
		terrain.LoadMap(CellSize, "Resource/Map/" + stageName + "_terrain.csv");


		//DataInfo terrainDataInfo = Load("Map/" + stageName + "_terrain.csv", terrain);
		//TerrainWidth = terrainDataInfo.Width;
		//TerrainHeight = terrainDataInfo.Height;

		assert(SpawnRangeX > 0 && SpawnRangeY > 0); // ちゃんと敵出現射程を設定してね
		// 敵出現射程の辞書初期化
		InitSpawnDic(SpawnRangeX, SpawnRangeY);
	}

	// デストラクタ
	~Map()
	{
		// マップデータのお掃除
		objects.clear();
		terrain.clear();
	}

	// 敵出現射程の辞書初期化【先に計算して辞書化】すると計算が必要なくなり【高速化する】
	//【注意！XとYの単位はマス目】
	void InitSpawnDic(int rangeCellX, int rangeCellY)
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
	int GetTerrain(float worldX, float worldY, float worldZ = -10000.0)
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

	int GetObjects(float worldX, float worldY, float worldZ = -10000.0)
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
	void DrawObjects()
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
					if (id == Spruce_1)
					{
						gm.mapObjects.push_back(std::make_shared<MapObjects>(x, 0, y, "Spruce_1"));
					}
				}
			}
			objectsLoad = true;
		}
	}

	//★地形を描く3D対応でY平面に描く
	void DrawTerrain()
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
				}
			}
			terrainLoad = true;
		}
	}
	int count = 0;

	// 指定された座標（ワールド座標）の地形が壁か調べる
	bool IsWall(float worldX, float worldY, float worldZ = -10000.0)
	{
		int objectsID = GetObjects(worldX, worldY, worldZ); // 指定された座標の地形のIDを取得

		return IsWall(objectsID);
	}

	//あるIDが壁かどうかだけ調べる
	bool IsWall(int objectsID)
	{
		for (int i = 0; i < sizeof(NotWallNums) / sizeof(NotWallNums[0]); i++)//[配列の数を求めるには]https://qiita.com/yohhoy/items/a2ab2900a2bd36c31879
		{   // 壁じゃない番号のとき
			if (objectsID == NotWallNums[i]) return false;
		}
		//SetTerrain(worldX, worldY, worldZ);
		//if (terrainID == 0) { printfDx("%d ", terrainID); printfDx("(%f %f)", worldX, worldZ); count++; }
		return (objectsID != -1);// (terrainID == Wall); // 地形が壁ならtrue、違うならfalseを返却する
	}

};

#endif