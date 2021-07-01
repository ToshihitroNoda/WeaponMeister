#ifndef PRODUCTIONSECTIONBASE_H_
#define PRODUCTIONSECTIONBASE_H_

#include "../../GameManager.h"
#include "../SceneManager.h"
#include <unordered_map>
#include <DxLib.h>

class ProductionSectionBase
{
public:
	GameManager& gm = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	ProductionSectionBase() = default;
	~ProductionSectionBase() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	static std::unordered_map<std::string, bool> canWeaponMake;
	static const std::string canWeaponMakeKeys[14];

protected:
	const int CsvSkipCell_ = 2;
	const int CsvTypeCheckFine_ = 5;
	const int CsvTypeCheck_ = 6;
	const int CsvNecessaryItem_ = 4;
	const int DrawMaxPouchSize_ = 42;
	const int lumberNum_ = 1;

	const int DetailWindowX_ = 600;
	const int DetailWindowY_ = 80;
	const int ItemNameX_ = 650;
	const int ItemNameY_ = 100;
	const int ItemQualityX_ = 900;
	const int ItemInfoX_ = 650;
	const int ItemInfoY_ = 200;

	static int cursorX_; // カーソル座標
	static int cursorY_;
	static int prevCursorY_;

	static int selectIconNum_;
	static int scrollCount_;
	static int weaponID_;
	static int ItemType_; // 選択できるアイテムの種類

	static bool weaponMakeAssert_;
	static bool itemDetail_;
	static bool cursorInit_;  // カーソルの初期化
	static bool shouldWeaponMainCreate_; // メイン部分作成フラグ
	static bool MainSlectOk_; // メイン部分選択完了フラグ
	static bool doAllFormat_;
	static bool shouldRetry_; // やりなおしフラグ
	static bool HandleSlectOk_; // 持ち手部分選択完了フラグ
	static bool shouldCreate_; // 精製フラグ

	static std::vector<int> itemForWeaponMake_;		  // 武器生成に必要なアイテムを一時的に保管するvector
	static std::vector<int> itemQualityForWeaponMake_;	  // 武器生成に必要なアイテムの品質を一時的に保管するvector
	static std::vector<int> ItemPosOnThePouch_;
	static std::vector<int> SelectItemPosOnThePouch_;
	static std::vector<int> PouchDrawErea_;
	static std::vector<int> NowDrawPosOnPouch_;

	void GetHandleForWeaponMake();
	void GetMainForWeaponMake(int ItemType);

	bool AlreadySecectItem(int ItemPosOnPouch);
};

#endif