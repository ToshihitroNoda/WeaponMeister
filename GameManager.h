#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Singleton.h"

#include <vector>
#include <memory>
#include <iostream>
#include <map>
#include <DxLib.h>
#include <assert.h>

#include "DataCsv.h"
#include "Image.h"


// CSVファイルの読込み
struct MapData : public DataCsv
{
	MapData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~MapData() { clear(); };//お掃除処理はこちら
	// csvファイルの読み込み
	void Load(std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadData(filePath);
	}
};

struct ItemData : public DataCsv
{
	ItemData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~ItemData() { clear(); };//お掃除処理はこちら
	// csvファイルの読み込み
	void Load(std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadData(filePath);
	}
};

struct WeaponData : public DataCsv
{
	WeaponData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~WeaponData() { clear(); };//お掃除処理はこちら
	// csvファイルの読み込み
	void Load(std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadData(filePath);
	}
};

struct ScoreData : public DataCsv
{
	ScoreData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~ScoreData() { clear(); };//お掃除処理はこちら
	// csvファイルの読み込み
	void Load(std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadData(filePath);
	}
};

class Map;
class Player;
class FieldItem;
class MapObjects;
class MapTerrain;

class GameManager : public Singleton<GameManager>
{
public:

	MapData mapData;
	ItemData itemData;
	WeaponData weaponData;
	ScoreData scoreData;
	Image image;

	friend class Singleton<GameManager>;				// Singletonでのインスタンス作成は許可

	std::shared_ptr<Map> map{ nullptr };				// マップ

	std::shared_ptr<Player> player{ nullptr };			// 自機の初期化

	std::vector<std::shared_ptr<FieldItem>> fieldItems; // フィールド上のアイテム

	std::vector<std::shared_ptr<MapObjects>> mapObjects;
	std::vector<std::shared_ptr<MapTerrain>> mapTerrain;

	// アイテム保管vector
	std::vector<int> pouch;
	std::vector<int> handles;
	std::vector<int> main;
	std::vector<int> weapons;

	// 品質保管vector
	std::vector<int> pouchQuality;
	std::vector<int> handlesQuality;
	std::vector<int> mainQuality;
	std::vector<int> weaponQuality;

	// 削除処理テンプレート
	template <typename T, class T_if>
	void EraseRemoveIf(std::vector<T>& v, T_if if_condition)
	{
		v.erase(
			std::remove_if(v.begin(), v.end(), if_condition),
			v.end()
		);
	};

	const int colorWhite = GetColor(255, 255, 255);
	const int colorBrack = GetColor(0, 0, 0);
	const int colorGray  = GetColor(122, 122, 122);
	const int colorRed   = GetColor(255, 0, 0);
	const int colorBlue  = GetColor(0, 100, 200);

	const int DefaultFontSize_ = 15;
	const int LastDay = 14;
	const int MaxPouchSize = 200;

	int money = 0;
	const int defaultMoney = 1000;

protected:
	GameManager()          = default;  // 外部からのインスタンス作成は禁止
	virtual ~GameManager() = default;  // 外部からのインスタンス破棄も禁止
};

#endif 

