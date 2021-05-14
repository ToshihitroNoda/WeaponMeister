#include <DxLib.h>
#include "MainMenu.h"
#include "Input.h"
#include "Image.h"

void MainMenu::Init()
{

}

void MainMenu::Final()
{

}

void MainMenu::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_DOWN))
	{
		if (CursorY_ != CursorY_Init_ + ((MenuStr_.size() - 1) * CursorY_Dist_))
			CursorY_ += CursorY_Dist_;
	}
	if (Input::GetButtonDown(PAD_INPUT_UP))
	{
		if (CursorY_ != CursorY_Init_)
			CursorY_ -= CursorY_Dist_;
	}

	if (CursorY_ == CursorY_Init_ && Input::GetButtonDown(PAD_INPUT_1))
	{
		sm.LoadScene("Adv");
	}
	else if (CursorY_ == CursorY_Init_ + CursorY_Dist_ && Input::GetButtonDown(PAD_INPUT_1))
	{
		return; // Œã‚ÅContinue
	}
	else if (CursorY_ == CursorY_Init_ + CursorY_Dist_ * 2 && Input::GetButtonDown(PAD_INPUT_1))
	{
		exit(0);
	}
}

void MainMenu::Draw()
{
	DrawGraph(0, 0, Image::mainmenuBack, TRUE);

	for (int i = 0; i < (unsigned)MenuStr_.size(); i++)
	{
		SetFontSize(FontSize_);
		DrawString(MenuStrX_Init_, MenuStrY_Init_ + (MenuStrY_Dist_ * i), MenuStr_[i].c_str(), gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}
	DrawGraph(CursorX_, CursorY_, Image::menuCursor, TRUE);
}