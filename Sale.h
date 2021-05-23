#ifndef SALE_H_
#define SALE_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "StageSelection.h"

class Sale : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	Sale() : Scene()
	{
		this->tag = "Sale";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

	static int saleAmount;
private:
	const int LastDay_ = 14;

	const int PouchWindowX_	 = 60;
	const int PouchWindowY_	 = 120;
	const int MoneyWindowX_	 = 60;
	const int MoneyWindowY_	 = 20;
	const int DetailWindowX_ = 600;
	const int DetailWindowY_ = 80;
	const int SaleButtonX_	 = 1000;
	const int SaleButtonY_	 = 650;

	const int CsvSkipCell_			= 2;
	const int CsvWeaponIdCell_		= 2;
	const int CsvWeaponBasePrice_	= 5;

	const int CursorX_Min_ItemSelect_				= 84;
	const int CursorY_Min_ItemSelect_				= 179;
	const int CursorX_Max_ItemSelect_			    = 444;
	const int CursorY_Max_ItemSelect_			    = 617;
	const int CursorX_MoveVerticalWidth_ItemSelect_ = 72;
	const int CursorY_MoveVerticalWidth_ItemSelect_ = 73;
	const int ItemID_ByLineBreak_ItemSelect_		= 6;
	const int itemX_								= 84;
	const int itemY_							    = 181;

	const int CursorX_ProceedNextPart_ = 997;
	const int CursorY_ProceedNextPart_ = 647;

	const int WindowX_CellSize_ = 6;
	const int WindowY_CellSize_ = 7;
	const int WindowCellSize_X_ = 72;
	const int WindowCellSize_Y_ = 73;

	const int ItemNameX_	= 650;
	const int ItemNameY_	= 100;
	const int ItemQualityX_ = 900;
	const int ItemInfoX_	= 650;
	const int ItemInfoY_	= 200;
	const int PriceX_		= 900;
	const int PriceY_		= 380;

	const int DrawMoneyX_	= 120;
	const int DrawMoneyY_	= 30;

	const int iconSize_		 = 66;	
	const int DrawMoneySize_ = 40;

	const int DrawMaxPouchSize_ = 42;

	int cursorX_	   = 0;	
	int cursorY_	   = 0;
	int prevCursorY_   = 0;
	int selectIconNum_ = 0;
	int prevMoney_ = 0;
	int scrollCount_ = 0;
	int operationDescriptionMassegeNum_ = 0;

	bool alradySelect_ = false;
	bool is_Operation_Description_Been_ = false;

	std::vector<int> weaponPosOnPouch_;
	std::vector<int> saleWeapons_;
	std::vector<int> selectWeaponPos_; // 選択した装備の位置を保存するvector
	std::vector<int> alreadySelectWeaponPos_; // 【既に】選択されている装備の位置を保存するvector
	std::vector<int> weaponPrice_; 
	std::vector<int> pouchDrawErea_;
	std::vector<int> nowDrawPosOnPouch_;

	std::string description_[7]
	{ "それでは先程作成した武器を売却しましょう。",
	  "最終日は勇者に売る武器一つのみしか売却することはできません。",
	  "最終日以外はいくつでも売却することができます。",
	  "矢印キーでカーソル移動、Zキーで選択することで売却する武器を選択できます。",
	  "選択を解除したい場合は選択済みの武器にカーソルを合わせてZキーでその武器の選択を解除できます。",
	  "売却したい武器をすべて選択し終えたらSALEボタンを押すことで次の画面に進みます。",
	  "以上が説明になります。店を継続させるための家賃を稼ぐ為に定期的に武器を売却しましょう。"
	};
};

#endif

