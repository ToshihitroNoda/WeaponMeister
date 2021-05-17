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
	const int Spruce_1		  = 1;    // 木
	const int Spruce_2		  = 2;
	const int Spruce_3		  = 3;
	const int Trunk			  = 4;
	const int Branch_1		  = 5;
	const int Branch_2		  = 6;
	const int Branch_3		  = 7;
	const int Branch_4		  = 8;
	const int BranchGroup	  = 9;
	const int Bush_1		  = 10;
	const int Bush_2		  = 11;
	const int Bush_3		  = 12;
	const int Bush_4		  = 13;
	const int BushLarge_1	  = 14;
	const int BushLarge_2	  = 15;
	const int CliffRock_1	  = 16;
	const int CliffRock_2	  = 17;
	const int CliffRock_3	  = 18;
	const int CliffRock_4	  = 19;
	const int CliffRock_5	  = 20;
	const int Rock_1		  = 21;
	const int Rock_2		  = 22;
	const int Rock_3		  = 23;
	const int Rock_4		  = 24;
	const int Rock_5		  = 25;
	const int Crystal_1		  = 26;
	const int Crystal_2		  = 27;
	const int Crystal_3		  = 28;
	const int Crystal_4		  = 29;
	const int Crystal_5		  = 30;

	std::vector<int> ObjectIDs
	{ Spruce_1,    Spruce_2,	Spruce_3,	 Trunk,		  Branch_1,	   Branch_2,	Branch_3,	 Branch_4, 
	  BranchGroup, Bush_1,	    Bush_2,		 Bush_3,	  Bush_4,	   BushLarge_1, BushLarge_2, CliffRock_1,
	  CliffRock_2, CliffRock_3, CliffRock_4, CliffRock_5, Rock_1,	   Rock_2,		Rock_3,		 Rock_4,		
	  Rock_5,	   Crystal_1,   Crystal_2,	 Crystal_3,   Crystal_4,   Crystal_5 };
	std::vector<std::string> ObjectNames
	{ "Spruce_1",	 "Spruce_2",	"Spruce_3",	   "Trunk",		  "Branch_1",  "Branch_2",	  "Branch_3",	 "Branch_4", 
	  "BranchGroup", "Bush_1",		"Bush_2",	   "Bush_3",	  "Bush_4",	   "BushLarge_1", "BushLarge_2", "CliffRock_1",
	  "CliffRock_2", "CliffRock_3", "CliffRock_4", "CliffRock_5", "Rock_1",	   "Rock_2",	  "Rock_3",		 "Rock_4", 
	  "Rock_5",		 "Crystal_1",	"Crystal_2",   "Crystal_3",	  "Crystal_4", "Crystal_5"};

	std::vector<int> ObjectWidths
	{
		120, 140, 40,  40,  540, 360, 270, 450, 560,  175, 180,
		270, 198, 240, 200, 660, 462, 450, 552, 1160, 297, 270,
		225, 320, 252, 175, 210, 162, 189, 138
	};
	std::vector<int> ObjectLengths
	{
		120, 140, 40,  180, 60,  40,  30,  50,  560, 250, 180,
		189, 220, 300, 225, 240, 294, 270, 920, 464, 231, 210,
		225, 320, 432, 245, 150, 162, 189, 161
	};

	//壁じゃないもの
	int NotWallNums[8] = { None, Fielditem, Bush_1, Bush_2, Bush_3, Bush_4, BushLarge_1, BushLarge_2 };

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
	void InitSpawnDic(int rangeCellX, int rangeCellY);

	// 指定された座標（ワールド座標）の地形データを取得する。
	int GetTerrain(float worldX, float worldY, float worldZ = -10000.0);

	int GetObjects(float worldX, float worldY, float worldZ = -10000.0);

	// ゲームオブジェクト描画
	void DrawObjects();

	//★地形を描く3D対応でY平面に描く
	void DrawTerrain();

	// 指定された座標（ワールド座標）の地形が壁か調べる
	bool IsWall(float worldX, float worldY, float worldZ = -10000.0);

	//あるIDが壁かどうかだけ調べる
	bool IsWall(int objectsID);

};

#endif