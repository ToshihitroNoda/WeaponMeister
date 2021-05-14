#ifndef BUY_H_
#define BUY_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "StageSelection.h"

class Buy : public Scene
{
public:
	GameManager& gm = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	Buy() : Scene()
	{
		this->tag = "Buy";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

	static int buyAmount;
private:
	StageSelection stageSelection;

	const int ShopWindowX_	  = 60;
	const int ShopWindowY_	  = 120;
	const int PouchWindowX_   = 740;
	const int PouchWindowY_   = 120;
	const int ArrowX_		  = 550;
	const int ArrowY_		  = 300;
	const int MoneyWindowX_	  = 60;
	const int MoneyWindowY_	  = 20;
	const int BuyMoneyXdist_  = 240;
	const int BuyY_			  = 650;

	const int CsvSkipCell_		  = 2;
	const int CsvItemIdCell_	  = 2;
	const int CsvItemMapCell_	  = 3;
	const int CsvItemQualityCell_ = 7;
	const int CsvItemPriceCell_	  = 8;

	const int CursorX_Min_ItemSelect_ = 84;
	const int CursorY_Min_ItemSelect_ = 180;
	const int CursorX_Max_ItemSelect_ = 444;
	const int CursorY_Max_ItemSelect_ = 472;
	const int CursorX_Buy_Select	  = 57;
	const int CursorY_Buy_Select	  = 647;	
	const int CursorX_MoveVerticalWidth_ItemSelect_ = 72;
	const int CursorY_MoveVerticalWidth_ItemSelect_ = 73;
	const int ItemID_ByLineBreak_ItemSelect_		= 6;
	const int Window_Icon_Columns_					= 7;

	const int itemX_	  = 84;
	const int itemY_	  = 182;
	const int pouchItemX_ = 764;

	const int DrawMoneyX_	 = 120;
	const int DrawMoneyY_	 = 30;
	const int DrawPriceX_    = 350;
	const int DrawMoneySize_ = 40;
	
	const int DetailWindowX_ = 600;
	const int DetailWindowY_ = 80;
	const int ItemNameX_	 = 650;
	const int ItemNameY_	 = 100;
	const int ItemQualityX_  = 900;
	const int ItemInfoX_	 = 650;
	const int ItemInfoY_	 = 200;

	const int PouchMax_		 = 42;

	int cursorX_	   = 0;	// カーソル座標
	int cursorY_	   = 0;
	int selectIconNum_ = 0;

	int beforeBuyPouchSize_ = 0;
	int beforeMoney_ = 0;

	bool itemDetail_ = false;

	std::vector<int> buyItems_;
	std::vector<int> buyItemsQuality_;

	std::vector<int> DrawItems_;
	int allLine_   = 0;
	int eraseLine_ = 0;
};

#endif 


