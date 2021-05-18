#include "Buy.h"
#include "Input.h"
#include "Image.h"

StageSelection stageSelection;

int Buy::buyAmount = 0;

void Buy::Init()
{
	gm.itemData.Load("Resource/Datas/ItemData.csv");
	
	for (int i = CsvSkipCell_; i < gm.itemData[0].size(); i++)
	{
		if ((int)gm.itemData[CsvItemMapCell_][i] <= StageSelection::stageNum - 1)
		{
			buyItems_.push_back((int)gm.itemData[CsvItemIdCell_][i]);
			buyItemsQuality_.push_back((int)gm.itemData[CsvItemQualityCell_][i]);
		}
	}

	cursorX_ = CursorX_Min_ItemSelect_;
	cursorY_ = CursorY_Min_ItemSelect_;

	beforeBuyPouchSize_ = gm.pouch.size();
	beforeMoney_ = gm.money;
}

void Buy::Final()
{
	sm.currentScene.reset();
}

void Buy::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_RIGHT))
	{
		if (cursorX_ < CursorX_Max_ItemSelect_ && cursorY_ != CursorY_Buy_Select)
		{
			cursorX_ += CursorX_MoveVerticalWidth_ItemSelect_;
			selectIconNum_++; // 選択されてる箇所のアイテムの番号を取得
		}
	}

	if (Input::GetButtonDown(PAD_INPUT_LEFT))
	{
		if (cursorX_ > CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
		{
			cursorX_ -= CursorX_MoveVerticalWidth_ItemSelect_;
			selectIconNum_--;
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_DOWN)) 
	{	
		if (cursorY_ != CursorY_Max_ItemSelect_ && cursorY_ != CursorY_Buy_Select)
		{
				cursorY_ += CursorY_MoveVerticalWidth_ItemSelect_;
				selectIconNum_ += ItemID_ByLineBreak_ItemSelect_;
		}
		else if (cursorY_ < CursorY_Buy_Select)
		{
			cursorX_ = CursorX_Buy_Select;
			cursorY_ = CursorY_Buy_Select;
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_UP))
	{
		if (cursorY_ != CursorY_Min_ItemSelect_ && cursorY_ != CursorY_Buy_Select)
		{
			cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
			selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;
		}
		else if (cursorY_ == CursorY_Buy_Select)
		{
			cursorX_ = CursorX_Min_ItemSelect_;
			cursorY_ = CursorY_Max_ItemSelect_;
		}
	}

	if (cursorX_ == CursorX_Buy_Select &&
		cursorY_ == CursorY_Buy_Select)
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			buyAmount = beforeMoney_ - gm.money;
			sm.LoadScene("Production");
		}
	}
	// 購入処理
	else
	{
		if (Input::GetButtonDown(PAD_INPUT_1) && 
			selectIconNum_ < buyItems_.size() && 
			gm.money >= (int)gm.itemData[CsvItemPriceCell_][buyItems_[selectIconNum_] + CsvSkipCell_])
		{
			gm.money -= (int)gm.itemData[CsvItemPriceCell_][buyItems_[selectIconNum_] + CsvSkipCell_];
			gm.pouch.push_back(buyItems_[selectIconNum_]);
			gm.pouchQuality.push_back(buyItemsQuality_[selectIconNum_]);
		}
	}

	// 購入やめる処理（選択済みアイテムの選択解除）
	if (Input::GetButtonDown(PAD_INPUT_2) && gm.pouch.size() > beforeBuyPouchSize_)
	{
		gm.money += (int)gm.itemData[CsvItemPriceCell_][gm.pouch.back() + CsvSkipCell_];
		gm.pouch.erase(gm.pouch.end() - 1);
		gm.pouchQuality.erase(gm.pouchQuality.end() - 1);
	}

	if (Input::GetButtonDown(PAD_INPUT_3) && selectIconNum_ < buyItems_.size())
	{
		if (!itemDetail_)
			itemDetail_ = true;
		else
			itemDetail_ = false;
	}
}

void Buy::Draw()
{
	DrawGraph(0, 0, Image::buyBack, TRUE);
	DrawGraph(MoneyWindowX_, MoneyWindowY_, Image::moneyWindow, TRUE);
	DrawGraph(MoneyWindowX_ + BuyMoneyXdist_, MoneyWindowY_, Image::salePriceWindow, TRUE);
	DrawGraph(ShopWindowX_, ShopWindowY_, Image::shopWindow, TRUE);
	DrawGraph(ArrowX_, ArrowY_, Image::arrow, TRUE);
	DrawGraph(PouchWindowX_, PouchWindowY_, Image::itemWindow, TRUE);
	DrawGraph(ShopWindowX_, BuyY_, Image::buy, TRUE); 

	SetFontSize(DrawMoneySize_);
	DrawString(DrawMoneyX_, DrawMoneyY_, std::to_string(gm.money).c_str(), gm.colorWhite);
	if (selectIconNum_ < buyItems_.size())
		DrawString(DrawPriceX_, DrawMoneyY_, std::to_string((int)gm.itemData[CsvItemPriceCell_][buyItems_[selectIconNum_] + CsvSkipCell_]).c_str(), gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);

	int x = 0;
	int y = 0;
	for (int i = 0; i < (unsigned)buyItems_.size(); i++)
	{
		DrawGraph
		(itemX_ + x * CursorX_MoveVerticalWidth_ItemSelect_,
		 itemY_ + y * CursorY_MoveVerticalWidth_ItemSelect_,
		 Image::itemIcons[buyItems_[x + (y * ItemID_ByLineBreak_ItemSelect_)]],
		 TRUE);

		if (x < ItemID_ByLineBreak_ItemSelect_ - 1)
		{
			x++;
		}
		else
		{
			x = 0;
			y++;
		}
	}

	DrawItems_ = gm.pouch;
	if (gm.pouch.size() > PouchMax_)
	{
		allLine_ = gm.pouch.size() / ItemID_ByLineBreak_ItemSelect_ + 1;
		eraseLine_ = allLine_ - Window_Icon_Columns_;
		DrawItems_.erase(DrawItems_.begin(), DrawItems_.begin() + eraseLine_ * ItemID_ByLineBreak_ItemSelect_);
	}
	int pouchX = 0;
	int pouchY = 0;
	for (int i = 0; i < DrawItems_.size(); i++)
	{
		DrawGraph
		(pouchItemX_ + pouchX * CursorX_MoveVerticalWidth_ItemSelect_,
		 itemY_ + pouchY * CursorY_MoveVerticalWidth_ItemSelect_,
		 Image::itemIcons[DrawItems_[pouchX + (pouchY * ItemID_ByLineBreak_ItemSelect_)]],
		 TRUE);

		if (pouchX < ItemID_ByLineBreak_ItemSelect_ - 1)
		{
			pouchX++;
		}
		else
		{
			pouchX = 0;
			pouchY++;
		}
	}

	if (cursorY_ <= CursorY_Max_ItemSelect_)
		DrawGraph(cursorX_, cursorY_, Image::itemSelection, TRUE);

	if (cursorY_ > CursorY_Max_ItemSelect_)
		DrawGraph(cursorX_, cursorY_, Image::nextCursor, TRUE);

	/*----- アイテムの詳細情報 -----*/
	if (itemDetail_)
	{
		DrawGraph(DetailWindowX_, DetailWindowY_, Image::detailWindow, TRUE);
		DrawString(ItemNameX_, ItemNameY_, gm.itemData[0][buyItems_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
		std::stringstream ss;
		ss << buyItemsQuality_[selectIconNum_];
		DrawString(ItemQualityX_, ItemNameY_, ("品質 : " + ss.str()).c_str(), gm.colorWhite);								// 品質 : 123(vector<int> -> charに変換)　にしたい。自分用メモ
		DrawString(ItemInfoX_, ItemInfoY_, gm.itemData[1][buyItems_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);

	}

	/*---------------*/
}