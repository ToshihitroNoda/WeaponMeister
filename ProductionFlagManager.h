#ifndef PRODUCTIONFLAGMANAGER_H_
#define PRODUCTIONFLAGMANAGER_H_

#include "ProductionSectionBase.h"

// Productionにフラグ情報を渡す仲介クラス
class ProductionFlagManager : ProductionSectionBase
{
public:
	ProductionFlagManager() = default;
	~ProductionFlagManager() = default;

	void Final()
	{
		weaponMakeAssert_         = weaponMakeAssert;
		itemDetail_               = itemDetail;
		cursorInit_               = cursorInit;  
		shouldWeaponMainCreate_   = shouldWeaponMainCreate; 
		MainSlectOk_              = MainSlectOk; 
		doAllFormat_              = doAllFormat;
		shouldRetry_              = shouldRetry; 
		HandleSlectOk_            = HandleSlectOk; 
		shouldCreate_             = shouldCreate;
		itemForWeaponMake_        = itemForWeaponMake;
		itemQualityForWeaponMake_ = itemQualityForWeaponMake;
		ItemPosOnThePouch_        = ItemPosOnThePouch;
		SelectItemPosOnThePouch_  = SelectItemPosOnThePouch;
		scrollCount_              = scrollCount;
	}

	void Update() override
	{
		weaponMakeAssert         = weaponMakeAssert_;
		itemDetail               = itemDetail_;
		cursorInit               = cursorInit_;  
		shouldWeaponMainCreate   = shouldWeaponMainCreate_; 
		MainSlectOk              = MainSlectOk_; 
		doAllFormat              = doAllFormat_;
		shouldRetry              = shouldRetry_; 
		HandleSlectOk            = HandleSlectOk_; 
		shouldCreate             = shouldCreate_;
		itemForWeaponMake        = itemForWeaponMake_;
		itemQualityForWeaponMake = itemQualityForWeaponMake_;
		ItemPosOnThePouch        = ItemPosOnThePouch_;
		SelectItemPosOnThePouch  = SelectItemPosOnThePouch_;
		scrollCount              = scrollCount_;
	}
	void Draw() override {}

	int scrollCount = 0;

	bool weaponMakeAssert = false;
	bool playErrorSound = false;
	bool itemDetail = false;
	bool cursorInit = true;  // カーソルの初期化
	bool shouldWeaponMainCreate = false; // メイン部分作成フラグ
	bool MainSlectOk = false; // メイン部分選択完了フラグ
	bool doAllFormat = false;
	bool MakeEnd = false;
	bool shouldRetry = false; // やりなおしフラグ
	bool HandleSlectOk = false; // 持ち手部分選択完了フラグ
	bool animationEnd = false;
	bool shouldCreate = false; // 精製フラグ

	std::vector<int> itemForWeaponMake;		  // 武器生成に必要なアイテムを一時的に保管するvector
	std::vector<int> itemQualityForWeaponMake;	  // 武器生成に必要なアイテムの品質を一時的に保管するvector
	std::vector<int> ItemPosOnThePouch;
	std::vector<int> SelectItemPosOnThePouch;
};

#endif