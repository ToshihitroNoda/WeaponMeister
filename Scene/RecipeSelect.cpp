#include "RecipeSelect.h"
#include "Input.h"
#include "Music.h"

void RecipeSelect::Init()
{
	gm.itemData.Load("Resource/Datas/ItemData.csv");
	gm.weaponData.Load("Resource/Datas/WeaponData.csv");

	cursorX_ = CursorX_Min_RecipeSelection_;
	cursorY_ = CursorY_Min_RecipeSelection_;
	weaponID_ = 0;

	for (int i = CsvSkipCell_; i < gm.weaponData[0].size(); i++)
	{
		weaponName_.push_back(gm.weaponData[0][i]);
	}
}

void RecipeSelect::Update()
{
	/*----- カーソル移動 -----*/
	if (Input::GetButtonDown(PAD_INPUT_RIGHT))
	{
		if (cursorX_ < CursorX_Max_RecipeSelection_)
		{
			PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
			cursorX_ = CursorX_Max_RecipeSelection_;
			prevCursorY_ = cursorY_;
			weaponID_++;
		}
		else
		{
			cursorX_ = CursorX_ProceedNextPart_;
			cursorY_ = CursorY_ProceedNextPart_;
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_LEFT))
	{
		if (cursorX_ > CursorX_Min_RecipeSelection_ && cursorX_ != CursorX_ProceedNextPart_)
		{
			PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
			cursorX_ = CursorX_Min_RecipeSelection_;
			weaponID_--;
		}
		else if (cursorX_ == CursorX_ProceedNextPart_)
		{
			PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
			cursorX_ = CursorX_Max_RecipeSelection_;
			cursorY_ = prevCursorY_;
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_DOWN) &&
		cursorY_ != CursorY_Max_RecipeSelection_ &&
		cursorX_ <= CursorX_Max_RecipeSelection_)
	{
		PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
		cursorY_ += CursorY_MoveVerticalWidth_RecipeSelect_;
		prevCursorY_ = cursorY_;
		weaponID_ += WeaponID_ByLineBreak_RecipeSelection_;
	}
	if (Input::GetButtonDown(PAD_INPUT_UP) &&
		cursorY_ != CursorY_Min_RecipeSelection_ &&
		cursorX_ <= CursorX_Max_RecipeSelection_)
	{
		PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
		cursorY_ -= CursorY_MoveVerticalWidth_RecipeSelect_;
		weaponID_ -= WeaponID_ByLineBreak_RecipeSelection_;
	}
	/*---------------*/

	/*----- 作る武器を決定 -----*/
	if (Input::GetKeyDown(KEY_INPUT_RETURN))
	{
		PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
		sm.LoadScene("Sale");
	}
	if (!Input::GetButtonDown(PAD_INPUT_1))
		return;

	if (cursorX_ == CursorX_ProceedNextPart_ && cursorY_ == CursorY_ProceedNextPart_)
	{
		PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
		sm.LoadScene("Sale");
	}
	else
	{
		PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
		if (canWeaponMake_[weaponID_ / 2])                  // 選択した武器が作れるなら
		{
			recipeSelection_ = true;                        // フラグを立てる

			if (weaponID_ < canWeaponMake_.size())          // 木製武器選択
			{
				ItemType_ = gm.itemData[CsvTypeCheck_][CsvSkipCell_];
				cursorInit_ = true;
			}
			else                                            // 石製武器選択
			{
				ItemType_ = gm.itemData[CsvTypeCheck_][gm.itemData[0].size() - 1];
				cursorInit_ = true;
			}
		}
	}
}

void RecipeSelect::Draw()
{
	DrawGraph(NextButtonX_, NextButtonY_, gm.image.end, TRUE);

	DrawGraph(WindowX_, RecipeWindowY_, gm.image.recipeWindow, TRUE);

	for (int i = 0; i < canWeaponMake_.size(); i++)
	{
		if (canWeaponMake_[i])
		{
			DrawString(DrawWeaponName_LeftLine_X_, DrawWeaponName_Y_ + (CursorY_MoveVerticalWidth_RecipeSelect_ * i), weaponName_[i * 2].c_str(), gm.colorWhite);
			DrawString(DrawWeaponName_RightLine_X_, DrawWeaponName_Y_ + (CursorY_MoveVerticalWidth_RecipeSelect_ * i), weaponName_[i * 2 + 1].c_str(), gm.colorWhite);
		}
	}

	if (cursorX_ < CursorX_ProceedNextPart_)
		DrawGraph(cursorX_, cursorY_, gm.image.recipeSelection, TRUE);
	else
		DrawGraph(cursorX_, cursorY_, gm.image.nextCursor, TRUE);
}
