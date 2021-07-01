#include <DxLib.h>
#include <filesystem>

#include "MainMenu.h"
#include "../MyLib/Input.h"
#include "../Music.h"

void MainMenu::Init()
{
	gm.image.Load(tag);
}

void MainMenu::Final()
{
	StopSoundMem(Music::op);
	gm.image.Final();
	sm.currentScene.reset();
}

void MainMenu::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_DOWN))
	{
		if (CursorY_ != CursorY_Init_ + ((MenuStr_.size() - 1) * CursorY_Dist_))
		{
			PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
			CursorY_ += CursorY_Dist_;
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_UP))
	{
		if (CursorY_ != CursorY_Init_)
		{
			PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
			CursorY_ -= CursorY_Dist_;
		}
	}

	if (CursorY_ == CursorY_Init_ && Input::GetButtonDown(PAD_INPUT_1))
	{
		PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
		isDead = true;
	}
	else if (CursorY_ == CursorY_Init_ + CursorY_Dist_ && Input::GetButtonDown(PAD_INPUT_1))
	{
		PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
		std::ifstream ifs("savedata.dat");
		if (ifs.is_open())
		{
			dataLoad_.Load();
			isDead = true;
		}
		else
			return;
	}
	else if (CursorY_ == CursorY_Init_ + CursorY_Dist_ * 2 && Input::GetButtonDown(PAD_INPUT_1))
	{
		PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
		exit(0);
	}
	count_++;
}

void MainMenu::Change()
{
	sm.LoadScene("Adv");
}

void MainMenu::Draw()
{
	DrawGraph(0, 0, gm.image.mainmenuBack, TRUE);

	for (int i = 0; i < (unsigned)MenuStr_.size(); i++)
	{
		SetFontSize(FontSize_);
		DrawString(MenuStrX_Init_, MenuStrY_Init_ + (MenuStrY_Dist_ * i), MenuStr_[i].c_str(), gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}
	if (count_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(CursorX_, CursorY_, gm.image.menuCursor, TRUE);
	}
}