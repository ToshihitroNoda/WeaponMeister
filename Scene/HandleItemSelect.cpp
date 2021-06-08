#include "HandleItemSelect.h"
#include "Input.h"
#include "Music.h"

void HandleItemSelect::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1) || Input::GetKeyDown(KEY_INPUT_RETURN))
	{
		if (cursorX_ <= CursorX_Max_ItemSelect_ && !Input::GetKeyDown(KEY_INPUT_RETURN))
		{
			if (!(selectIconNum_ < itemForWeaponMake_.size()))
				return;
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			if (gm.handles.size() < HandleSelect_MaxSize_ && !AlreadySecectItem(ItemPosOnThePouch_[selectIconNum_])) // 重複していなかったら
			{
				gm.handles.push_back(itemForWeaponMake_[selectIconNum_]);
				gm.handlesQuality.push_back(itemQualityForWeaponMake_[selectIconNum_]);
				SelectItemPosOnThePouch_.push_back(NowDrawPosOnPouch_[selectIconNum_ - scrollCount_ * WindowX_CellSize_]);
			}
			else
			{
				for (int i = 0; i < gm.handles.size(); i++)
				{
					if (SelectItemPosOnThePouch_[i] == NowDrawPosOnPouch_[selectIconNum_ - scrollCount_ * WindowX_CellSize_])
					{
						gm.handles.erase(gm.handles.begin() + i);
						gm.handlesQuality.erase(gm.handlesQuality.begin() + i);
						SelectItemPosOnThePouch_.erase(SelectItemPosOnThePouch_.begin() + i);
					}
				}
			}

		}
		// 次へ
		else
		{
			if (HandleSlectOk_)
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				cursorX_ = CursorX_Min_ItemSelect_;			// カーソル位置初期化
				cursorY_ = CursorY_Min_ItemSelect_;
				selectIconNum_ = 0;							// 選択中の番号初期化
				shouldWeaponMainCreate_ = true;
				itemDetail_ = false;						// アイテム詳細ウィンドウフラグ初期化
				itemForWeaponMake_.clear();					// 選択できるアイテムリストをクリア
				itemQualityForWeaponMake_.clear();
				ItemPosOnThePouch_.clear();					// 選択できるアイテムポーチ内の位置情報をクリア

				// メイン部分で選択できるものをvectorに保管
				GetMainForWeaponMake(ItemType_);
			}
			else
			{
				weaponMakeAssert_ = true;
			}
		}
	}

	if (Input::GetButtonDown(PAD_INPUT_2))
	{
		PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
		doAllFormat_ = true;
	}
	if (Input::GetButtonDown(PAD_INPUT_3) && selectIconNum_ < itemForWeaponMake_.size())
	{
		PlaySoundMem(Music::menuopen_SE, DX_PLAYTYPE_BACK);
		if (!itemDetail_)
			itemDetail_ = true;
		else
			itemDetail_ = false;
	}

	if (gm.handles.size() >= 1)
	{
		HandleSlectOk_ = true;
	}
	else
	{
		HandleSlectOk_ = false;
	}

	// 詳細ウィンドウ表示したままカーソル移動しても閉じるように
	if (selectIconNum_ >= itemForWeaponMake_.size())
		itemDetail_ = false;
}

void HandleItemSelect::Draw()
{
	for (int i = 0; i < gm.handles.size(); i++)
	{
		if (gm.handles.size() > 0)
		{
			// 選択したものを描画
			DrawGraph
			(AlreadySelect_HandleItem_X_ + i * AlreadySelect_HandleItem_X_Diameter_,
			 AlreadySelect_HandleItem_Y_,
			 gm.image.itemIcons[gm.handles[i]],
			 TRUE);
		}
	}
}
