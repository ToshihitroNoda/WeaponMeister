#include "Buy.h"
#include "Input.h"
#include "Adv.h"
#include "Music.h"

StageSelection stageSelection;

int Buy::buyAmount = 0;

void Buy::Init()
{
	gm.image.Load(tag);
	gm.itemData.Load("Resource/Datas/ItemData.csv");
	
	for (int i = CsvSkipCell_; i < gm.itemData[0].size(); i++)
	{
		if ((int)gm.itemData[CsvItemMapCell_][i] <= StageSelection::stageNum - 1)
		{
			buyItems_.push_back((int)gm.itemData[CsvItemIdCell_][i]);
			buyItemsQuality_.push_back((int)gm.itemData[CsvItemQualityCell_][i]);
		}
	}
	
	if (Adv::day != 1)
		is_Operation_Description_Been_ = true;

	cursorX_ = CursorX_Min_ItemSelect_;
	cursorY_ = CursorY_Min_ItemSelect_;

	beforeBuyPouchSize_ = gm.pouch.size();
	beforeMoney_ = gm.money;

	PlaySoundMem(Music::buy_BGM, DX_PLAYTYPE_LOOP);
}

void Buy::Final()
{
	StopSoundMem(Music::buy_BGM);
	PlaySoundMem(Music::production_BGM, DX_PLAYTYPE_LOOP);
	gm.image.Final();
	sm.currentScene.reset();
}

void Buy::Update()
{
	if (is_Operation_Description_Been_)
	{
		if (Input::GetButtonDown(PAD_INPUT_RIGHT))
		{
			if (cursorX_ < CursorX_Max_ItemSelect_ && cursorY_ != CursorY_Buy_Select)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ += CursorX_MoveVerticalWidth_ItemSelect_;
				selectIconNum_++; // 選択されてる箇所のアイテムの番号を取得
			}
		}

		if (Input::GetButtonDown(PAD_INPUT_LEFT))
		{
			if (cursorX_ > CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ -= CursorX_MoveVerticalWidth_ItemSelect_;
				selectIconNum_--;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_DOWN))
		{
			if (cursorY_ != CursorY_Max_ItemSelect_ && cursorY_ != CursorY_Buy_Select)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorY_ += CursorY_MoveVerticalWidth_ItemSelect_;
				selectIconNum_ += ItemID_ByLineBreak_ItemSelect_;
			}
			else if (cursorY_ < CursorY_Buy_Select)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ = CursorX_Buy_Select;
				cursorY_ = CursorY_Buy_Select;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_UP))
		{
			if (cursorY_ != CursorY_Min_ItemSelect_ && cursorY_ != CursorY_Buy_Select)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
				selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;
			}
			else if (cursorY_ == CursorY_Buy_Select)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ = CursorX_Min_ItemSelect_;
				cursorY_ = CursorY_Max_ItemSelect_;
			}
		}

		if (cursorX_ == CursorX_Buy_Select &&
			cursorY_ == CursorY_Buy_Select)
		{
			if (Input::GetButtonDown(PAD_INPUT_1))
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				buyAmount = beforeMoney_ - gm.money;
				sm.LoadScene("Production");
			}
		}
		// 購入処理
		else
		{
			if (Input::GetButtonDown(PAD_INPUT_1) &&
				selectIconNum_ < buyItems_.size() &&
				gm.pouch.size() < PouchMaxSize_   &&
				gm.money >= (int)gm.itemData[CsvItemPriceCell_][buyItems_[selectIconNum_] + CsvSkipCell_])
			{
				PlaySoundMem(Music::money_SE, DX_PLAYTYPE_BACK);
				gm.money -= (int)gm.itemData[CsvItemPriceCell_][buyItems_[selectIconNum_] + CsvSkipCell_];
				gm.pouch.push_back(buyItems_[selectIconNum_]);
				gm.pouchQuality.push_back(buyItemsQuality_[selectIconNum_]);
			}
		}

		// 購入やめる処理（選択済みアイテムの選択解除）
		if (Input::GetButtonDown(PAD_INPUT_2) && gm.pouch.size() > beforeBuyPouchSize_)
		{
			PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
			gm.money += (int)gm.itemData[CsvItemPriceCell_][gm.pouch.back() + CsvSkipCell_];
			gm.pouch.erase(gm.pouch.end() - 1);
			gm.pouchQuality.erase(gm.pouchQuality.end() - 1);
		}

		if (Input::GetButtonDown(PAD_INPUT_3) && selectIconNum_ < buyItems_.size())
		{
			PlaySoundMem(Music::menuopen_SE, DX_PLAYTYPE_BACK);
			if (!itemDetail_)
				itemDetail_ = true;
			else
				itemDetail_ = false;
		}

		// 詳細ウィンドウ表示したままカーソル移動しても閉じるように
		if (selectIconNum_ >= buyItems_.size())
			itemDetail_ = false;
	}
	else
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			if (operationDescriptionMassegeNum_ < sizeof(description_) / sizeof(*description_) - 1)
				operationDescriptionMassegeNum_++;
			else
				is_Operation_Description_Been_ = true;
		}
	}
}

void Buy::Draw()
{
	DrawGraph(0, 0, gm.image.buyBack, TRUE);
	DrawGraph(MoneyWindowX_, MoneyWindowY_, gm.image.moneyWindow, TRUE);
	DrawGraph(MoneyWindowX_ + BuyMoneyXdist_, MoneyWindowY_, gm.image.salePriceWindow, TRUE);
	DrawGraph(ShopWindowX_, ShopWindowY_, gm.image.shopWindow, TRUE);
	DrawGraph(ArrowX_, ArrowY_, gm.image.arrow, TRUE);
	DrawGraph(PouchWindowX_, PouchWindowY_, gm.image.itemWindow, TRUE);
	DrawGraph(ShopWindowX_, BuyY_, gm.image.buy, TRUE);

	SetFontSize(DrawMoneySize_);
	DrawString(DrawMoneyX_, DrawMoneyY_, std::to_string(gm.money).c_str(), gm.colorWhite);
	if (selectIconNum_ < buyItems_.size())
		DrawString(DrawPriceX_, DrawMoneyY_, std::to_string((int)gm.itemData[CsvItemPriceCell_][buyItems_[selectIconNum_] + CsvSkipCell_]).c_str(), gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);

	int x = 0;
	int y = 0;
	for (size_t i = 0; i < buyItems_.size(); i++)
	{
		DrawGraph
		(itemX_ + x * CursorX_MoveVerticalWidth_ItemSelect_,
		 itemY_ + y * CursorY_MoveVerticalWidth_ItemSelect_,
			gm.image.itemIcons[buyItems_[x + (y * ItemID_ByLineBreak_ItemSelect_)]],
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
	if (gm.pouch.size() > DrawPouchMax_)
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
			gm.image.itemIcons[DrawItems_[pouchX + (pouchY * ItemID_ByLineBreak_ItemSelect_)]],
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
		DrawGraph(cursorX_, cursorY_, gm.image.itemSelection, TRUE);

	if (cursorY_ > CursorY_Max_ItemSelect_)
		DrawGraph(cursorX_, cursorY_, gm.image.nextCursor, TRUE);

	/*----- アイテムの詳細情報 -----*/
	if (itemDetail_)
	{
		DrawGraph(DetailWindowX_, DetailWindowY_, gm.image.detailWindow, TRUE);
		DrawString(ItemNameX_, ItemNameY_, gm.itemData[0][buyItems_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
		std::stringstream ss;
		ss << buyItemsQuality_[selectIconNum_];
		DrawString(ItemQualityX_, ItemNameY_, ("品質 : " + ss.str()).c_str(), gm.colorWhite);								// 品質 : 123(vector<int> -> charに変換)　にしたい。自分用メモ
		DrawString(ItemInfoX_, ItemInfoY_, gm.itemData[1][buyItems_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);

	}

	/*---------------*/

	if (!is_Operation_Description_Been_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		std::string drawNextDescription = "Zキーで次へ";
		int DrawWidthUnder = GetDrawStringWidth(drawNextDescription.c_str(), -1);
		DrawString((Screen::width - DrawWidthUnder) / 2, (Screen::height - (Screen::height / 4) + 30), drawNextDescription.c_str(), gm.colorWhite);
		std::string drawMassege = description_[operationDescriptionMassegeNum_];
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}
}