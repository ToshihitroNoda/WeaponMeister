#include "ItemSelect.h"
#include "Input.h"
#include "Music.h"
#include "HandleItemSelect.h"
#include "MainItemSelect.h"
#include "CreateRun.h"

HandleItemSelect handleItemSelectSection;
MainItemSelect   mainItemSelectSection;

void ItemSelect::Update()
{
	if (!weaponMakeAssert_)
	{
		if (cursorInit_) // カーソル位置初期化
		{
			cursorX_ = CursorX_Min_ItemSelect_;
			cursorY_ = CursorY_Min_ItemSelect_;
			selectIconNum_ = 0;
			cursorInit_ = false;

			// 持ち手部分で選択できるものをvectorに保管
			GetHandleForWeaponMake();
		}

		/*----- カーソル移動 -----*/

		if (Input::GetButtonDown(PAD_INPUT_RIGHT))
		{
			if (cursorX_ < CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ += CursorX_MoveVerticalWidth_ItemSelect_;
				prevCursorY_ = cursorY_;
				selectIconNum_++; // 選択されてる箇所のアイテムの番号を取得
			}
			else
			{
				cursorX_ = CursorX_ProceedNextPart_;
				cursorY_ = CursorY_ProceedNextPart_;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_LEFT))
		{
			if (cursorX_ > CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ -= CursorX_MoveVerticalWidth_ItemSelect_;
				prevCursorY_ = cursorY_;
				selectIconNum_--;
			}
			else if (cursorX_ > CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ = CursorX_Max_ItemSelect_;
				cursorY_ = prevCursorY_;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_DOWN))
		{
			if (cursorY_ != CursorY_Max_ItemSelect_ &&
				cursorX_ <= CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorY_ += CursorY_MoveVerticalWidth_ItemSelect_;
				prevCursorY_ = cursorY_;
				selectIconNum_ += ItemID_ByLineBreak_ItemSelect_;
			}
			else if (cursorX_ <= CursorX_Max_ItemSelect_)
			{
				if (itemForWeaponMake_.size() > DrawMaxPouchSize_)
				{
					if (PouchDrawErea_.size() > WindowX_CellSize_)
					{
						PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
						prevCursorY_ = cursorY_;
						selectIconNum_ += ItemID_ByLineBreak_ItemSelect_;

						// 一行スクロール
						scrollCount_++;
						// 描画するアイテムのvectorの最初の一行を削除し、後ろに一行足す
						// まず先頭の一行の削除
						PouchDrawErea_.erase(PouchDrawErea_.begin(), PouchDrawErea_.begin() + WindowX_CellSize_);
						NowDrawPosOnPouch_.erase(NowDrawPosOnPouch_.begin(), NowDrawPosOnPouch_.begin() + WindowX_CellSize_);
						// 後ろに一行追加。
						/// iの初期値		: 表示できる最大数 + 追加する列数 - 列数
						/// for文の回る条件 : 表示できる最大数 + 追加する列数まで
						for (int i = DrawMaxPouchSize_ + (scrollCount_ * WindowX_CellSize_) - WindowX_CellSize_;
							i < DrawMaxPouchSize_ + (scrollCount_ * WindowX_CellSize_);
							i++)
						{
							if (i < itemForWeaponMake_.size())
							{
								PouchDrawErea_.push_back(itemForWeaponMake_[i]);
								NowDrawPosOnPouch_.push_back(ItemPosOnThePouch_[i]);
							}
						}
					}
				}
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_UP))
		{
			if (cursorY_ != CursorY_Min_ItemSelect_ &&
				cursorX_ <= CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
				prevCursorY_ = cursorY_;
				selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;
			}
			else if (cursorX_ <= CursorX_Max_ItemSelect_)
			{
				if (scrollCount_ > 0)
				{
					PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
					prevCursorY_ = cursorY_;
					selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;

					scrollCount_--;
					if (PouchDrawErea_.size() == DrawMaxPouchSize_)		// 描画されてるウィンドウが埋まってる場合
					{
						PouchDrawErea_.erase(PouchDrawErea_.end() - WindowX_CellSize_, PouchDrawErea_.end());
						NowDrawPosOnPouch_.erase(NowDrawPosOnPouch_.end() - WindowX_CellSize_, NowDrawPosOnPouch_.end());
						// 描画するアイテムのvectorの最初に描画されてない一行分追加
						for (int i = WindowX_CellSize_; i > 0; i--)
						{
							PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), itemForWeaponMake_[scrollCount_ * WindowX_CellSize_ + i - 1]);
							NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), ItemPosOnThePouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
						}
					}
					else if (PouchDrawErea_.size() > DrawMaxPouchSize_ - WindowX_CellSize_ &&
						PouchDrawErea_.size() < DrawMaxPouchSize_)		// 描画されてるウィンドウの最後の一行に空きがある場合
					{
						PouchDrawErea_.erase(PouchDrawErea_.end() - (PouchDrawErea_.size() % WindowX_CellSize_), PouchDrawErea_.end());
						NowDrawPosOnPouch_.erase(NowDrawPosOnPouch_.end() - (NowDrawPosOnPouch_.size() % WindowX_CellSize_), NowDrawPosOnPouch_.end());
						// 描画するアイテムのvectorの最初に描画されてない一行分追加
						for (int i = WindowX_CellSize_; i > 0; i--)
						{
							PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), itemForWeaponMake_[scrollCount_ * WindowX_CellSize_ + i - 1]);
							NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), ItemPosOnThePouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
						}
					}
					else												// 描画されてるウィンドウの下何行かが空いている場合
					{
						// 描画するアイテムのvectorの最初に描画されてない一行分追加
						for (int i = WindowX_CellSize_; i > 0; i--)
						{
							PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), itemForWeaponMake_[scrollCount_ * WindowX_CellSize_ + i - 1]);
							NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), ItemPosOnThePouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
						}
					}
				}
			}
		}

		/*---------------*/

		// 持ち手部分素材選択
		if (!shouldWeaponMainCreate_)
		{
			handleItemSelectSection.Update();
		}

		// メイン部分素材選択 
		else
		{
			mainItemSelectSection.Update();
		}
	}
	else
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			weaponMakeAssert_ = false;
			playErrorSound = false;
		}
	}
}

void ItemSelect::Draw()
{
	DrawGraph(WindowX_, WindowY_, gm.image.itemWindow, TRUE);
	DrawGraph(SelectItemWindowX_, WindowY_, gm.image.selectItemWindow, TRUE);
	DrawGraph(NextButtonX_, NextButtonY_, gm.image.next, TRUE);

	if (!shouldWeaponMainCreate_)
		DrawGraph(ArrowX_, ArrowYHandle_, gm.image.productionArrow, TRUE);
	else
		DrawGraph(ArrowX_, ArrowYMain_, gm.image.productionArrow, TRUE);

	for (int y = 0; y < WindowY_CellSize_; y++)
	{
		for (int x = 0; x < WindowX_CellSize_; x++)
		{
			if ((x + (y * WindowX_CellSize_)) < PouchDrawErea_.size())
			{
				DrawGraph(itemX_ + x * WindowCellSize_X_, itemY_ + y * WindowCellSize_Y_, gm.image.itemIcons[PouchDrawErea_[x + (y * WindowX_CellSize_)]], TRUE);
			}
		}
	}


	int shadowY = 0;
	int shadowX = 0;
	for (int i = 0; i < SelectItemPosOnThePouch_.size(); i++)
	{
		for (int j = 0; j < NowDrawPosOnPouch_.size(); j++)
		{
			if (SelectItemPosOnThePouch_[i] == NowDrawPosOnPouch_[j])
			{
				if (j < ItemID_ByLineBreak_ItemSelect_)
				{
					shadowX = j;
					shadowY = 0;
				}
				else
				{
					shadowX = j - ItemID_ByLineBreak_ItemSelect_ * (j / ItemID_ByLineBreak_ItemSelect_);
					shadowY = j / ItemID_ByLineBreak_ItemSelect_;
				}

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
				DrawBox
				(itemX_ + (shadowX * CursorX_MoveVerticalWidth_ItemSelect_),
					itemY_ + (shadowY * CursorY_MoveVerticalWidth_ItemSelect_),
					itemX_ + (shadowX * CursorX_MoveVerticalWidth_ItemSelect_ + iconSize_),
					itemY_ + (shadowY * CursorY_MoveVerticalWidth_ItemSelect_ + iconSize_),
					gm.colorGray,
					TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				DrawString
				(itemX_ + (shadowX * CursorX_MoveVerticalWidth_ItemSelect_),
					itemY_ + (shadowY * CursorY_MoveVerticalWidth_ItemSelect_),
					"選択中",
					gm.colorWhite);
			}
		}
	}

	// 必要素材の描画
	DrawGraph(AlreadySelect_MainItem_X_, MakeWeaponY_, gm.image.itemIcons[(int)gm.weaponData[CsvNecessaryItem_][weaponID_ + CsvSkipCell_]], TRUE);

	// 作る武器の描画
	DrawGraph(MakeWeaponX_, MakeWeaponY_, gm.image.weaponIcons[weaponID_], TRUE);

	// 持ち手部分の素材描画
	handleItemSelectSection.Draw();

	// メイン部分の素材描画 
	mainItemSelectSection.Draw();

	if (cursorX_ >= CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
		DrawGraph(cursorX_, cursorY_, gm.image.itemSelection, TRUE);

	if (cursorX_ > CursorX_Max_ItemSelect_)
		DrawGraph(cursorX_, cursorY_, gm.image.nextCursor, TRUE);

	/*----- アイテムの詳細情報 -----*/
	if (itemDetail_)
	{
		DrawGraph(DetailWindowX_, DetailWindowY_, gm.image.detailWindow, TRUE);
		DrawString(ItemNameX_, ItemNameY_, gm.itemData[0][itemForWeaponMake_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
		std::stringstream ss;
		ss << itemQualityForWeaponMake_[selectIconNum_ + scrollCount_ * WindowX_CellSize_];
		DrawString(ItemQualityX_, ItemNameY_, ("品質 : " + ss.str()).c_str(), gm.colorWhite);								// 品質 : 123(vector<int> -> charに変換)　にしたい。自分用メモ
		DrawString(ItemInfoX_, ItemInfoY_, gm.itemData[1][itemForWeaponMake_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);

	}

	/*---------------*/


	/*-----品質描画-----*/
	int drawWeaponQualityStorage = 0; // 品質保存用変数

	for (int i = 0; i < gm.handles.size(); i++)
	{
		drawWeaponQualityStorage += (gm.handlesQuality[i] / ((i + 1) * 2)); // 全素材の品質を計算(持ち手部分)
	}
	for (int i = 0; i < gm.main.size(); i++)
	{
		drawWeaponQualityStorage += (gm.mainQuality[i] / ((i + 1) * 2));	// 全素材の品質を計算(上で計算した持ち手部分 + メイン部分)
	}

	DrawString(MakeWeaponQualityX_, MakeWeaponQualityY_, std::to_string(drawWeaponQualityStorage).c_str(), gm.colorWhite);


	/*---------------*/
	SetFontSize(15);
	DrawString(OptionMenuX_, OptionMenuY_, "←↑→↓ : カーソル移動　,　Zキー : 選択 ・ 選択解除　,　Xキー : 一つ前へ  ,  Cキー : アイテム詳細", gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);
}
