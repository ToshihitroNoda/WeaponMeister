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
#include "FieldItem.h"
#include "MapObjects.h"
#include "MapTerrain.h"
#include "DataCsv.h"

// CSVファイルの読込み & 当たり判定可能なマス目
struct CsvCell : public DataCsv
{
	int noneData = -1; // この値のCSVデータはデータがないマスとみなす
	int cellSize = 1;
	CsvCell(int CellSize = 1, std::string filePath = "") : DataCsv(filePath)
	{
		assert(CellSize > 0 && "マス目サイズ指定CellSizeは1以上に設定して！" != "");
		this->cellSize = CellSize;
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
	const int None            = -1; // 何も無いマス
	const int Terrain_Grass   = 0;  // 草の地面
	const int Tterrain_Sand   = 1;  // 砂の地面
	const int Terrain_Stone   = 2;  // 石の地面
	const int Terrain_Volcano = 3;  // 火山の地面

	const int Fielditem   = 0;
	const int Spruce_1    = 1;
	const int Spruce_2    = 2;
	const int Spruce_3    = 3;
	const int Trunk       = 4;
	const int Branch_1    = 5;
	const int Branch_2    = 6;
	const int Branch_3    = 7;
	const int Branch_4    = 8;
	const int BranchGroup = 9;
	const int Bush_1      = 10;
	const int Bush_2      = 11;
	const int Bush_3      = 12;
	const int Bush_4      = 13;
	const int BushLarge_1 = 14;
	const int BushLarge_2 = 15;
	const int CliffRock_1 = 16;
	const int CliffRock_2 = 17;
	const int CliffRock_3 = 18;
	const int CliffRock_4 = 19;
	const int CliffRock_5 = 20;
	const int Rock_1      = 21;
	const int Rock_2      = 22;
	const int Rock_3      = 23;
	const int Rock_4      = 24;
	const int Rock_5      = 25;
	const int Crystal_1   = 26;
	const int Crystal_2   = 27;
	const int Crystal_3   = 28;
	const int Crystal_4   = 29;
	const int Crystal_5   = 30;

public:
	GameManager& gm = GameManager::GetInstance();

	std::vector<int> objectIDs
	{ Spruce_1,    Spruce_2,    Spruce_3,    Trunk,       Branch_1,    Branch_2,    Branch_3,    Branch_4,
	  BranchGroup, Bush_1,      Bush_2,      Bush_3,      Bush_4,      BushLarge_1, BushLarge_2, CliffRock_1,
	  CliffRock_2, CliffRock_3, CliffRock_4, CliffRock_5, Rock_1,      Rock_2,      Rock_3,      Rock_4,
	  Rock_5,      Crystal_1,   Crystal_2,   Crystal_3,   Crystal_4,   Crystal_5 };

	std::vector<std::string> objectNames
	{ "Spruce_1",    "Spruce_2",    "Spruce_3",    "Trunk",       "Branch_1",  "Branch_2",	  "Branch_3",	 "Branch_4",
	  "BranchGroup", "Bush_1",      "Bush_2",      "Bush_3",      "Bush_4",    "BushLarge_1", "BushLarge_2", "CliffRock_1",
	  "CliffRock_2", "CliffRock_3", "CliffRock_4", "CliffRock_5", "Rock_1",    "Rock_2",	  "Rock_3",		 "Rock_4",
	  "Rock_5",      "Crystal_1",   "Crystal_2",   "Crystal_3",   "Crystal_4", "Crystal_5" };

	// マス目のXとYを保持するデータ型
	struct CellXY
	{
		int X = 0;
		int Y = 0;
		CellXY(int X, int Y) : X{ X }, Y{ Y }
		{};
		bool operator < (const CellXY& otherXY) const {
			if (Y < otherXY.Y) return true;  // Y優先並べ替え
			if (Y > otherXY.Y) return false;
			if (X < otherXY.X) return true;  // Yが同じ時はXを比較
			if (X > otherXY.X) return false;
			return false;                    // 完全一致のときは
		}
	};

	// コンストラクタ
	// startPosition : 開始位置（デバッグやリスタート時に、面の途中から開始できるように）
	// filePath : CSVファイルのパス
	Map(float startPosition, std::string stageName)
	{
		positionX_ = startPosition;
		objectsLoad_ = false;

		objects_.LoadMap(cellSize_, "Resource/Map/" + stageName + "_objects.csv");
		terrain_.LoadMap(cellSize_, "Resource/Map/" + stageName + "_terrain.csv");

		std::ifstream ifs("Resource/Map/" + stageName + "_objects2.csv");
		if (ifs.is_open())
		{
			objects2_.LoadMap(cellSize_, "Resource/Map/" + stageName + "_objects2.csv");
		}
		std::ifstream fs("Resource/Map/" + stageName + "_objects3.csv");
		if (fs.is_open())
		{
			objects3_.LoadMap(cellSize_, "Resource/Map/" + stageName + "_objects3.csv");
		}
		assert(spawnRangeX_ > 0 && spawnRangeY_ > 0); // ちゃんと敵出現射程を設定してね
		// 敵出現射程の辞書初期化
		InitSpawnDic(spawnRangeX_, spawnRangeY_);
	}

	// デストラクタ
	~Map()
	{
		// マップデータのお掃除
		objects_.clear();
		objects2_.clear();
		objects3_.clear();
		terrain_.clear();
	}

	// 敵出現射程の辞書初期化【先に計算して辞書化】すると計算が必要なくなり【高速化する】
	//【注意！XとYの単位はマス目】
	void InitSpawnDic(int rangeCellX, int rangeCellY);

	// ゲームオブジェクト描画
	void LoadObjects();

	//地形を描く3D対応でY平面に描く
	void LoadTerrain();

private:

	std::vector<int> objectWidths_
	{
		120, 140, 40,  40,  540, 360, 270, 450, 560,  175, 180,
		270, 198, 240, 200, 660, 462, 450, 552, 1160, 297, 270,
		225, 320, 252, 175, 210, 162, 189, 138
	};
	std::vector<int> objectLengths_
	{
		120, 140, 40,  180, 60,  40,  30,  50,  560, 250, 180,
		189, 220, 300, 225, 240, 294, 270, 920, 464, 231, 210,
		225, 320, 432, 245, 150, 162, 189, 161
	};

	int spawnRangeX_ = 30; // オブジェクト出現射程スポーンレンジ【注意！Xの単位はマス目】
	int spawnRangeY_ = 30; // オブジェクト出現射程スポーンレンジ【注意！Yの単位はマス目】

	std::map<CellXY, bool> spawnDic_;

	const int cellSize_ = 32; // マップの1マスのピクセル数

	bool isRotaGraph_ = true; // DrawRotaGraphを使うときはマス目サイズ/2ずらす必要がある

	// 画像の中心を起点に描く場合のずれ
	float rotaGraphShiftX_ = (isRotaGraph_) ? (float)cellSize_ / 2 : 0.0f;
	float rotaGraphShiftY_ = (isRotaGraph_) ? (float)cellSize_ / 2 : 0.0f;
	float rotaGraphShiftZ_ = (isRotaGraph_) ? (float)cellSize_ / 2 : 0.0f;

	CsvCell terrain_;  // 地面データ
	CsvCell objects_;  // 地形（岩とか木とか）データ
	CsvCell objects2_;
	CsvCell objects3_;

	int terrainWidth_  = 0;  // マップデータの横のマス数
	int terrainHeight_ = 0;  // マップデータの縦のマス数
	float positionX_   = 0;  // 現在の位置（マップ左端の座標）
	float positionY_   = 0;  // 現在の位置（マップ上端の座標）

	bool objectsLoad_  = false;
	bool objects2Load_ = false;
	bool objects3Load_ = false;
	bool terrainLoad_  = false;

};

#endif