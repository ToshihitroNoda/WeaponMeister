#include "Game.h"

#include "Screen.h"
#include "MyRandom.h"
#include "Input.h"
#include "Music.h"

void Game::Init()
{
	Input::Init();
	MyRandom::Init();
	ChangeFont("UD ƒfƒWƒ^ƒ‹ ‹³‰È‘‘Ì N-B");
	ChangeFontType(DX_FONTTYPE_EDGE);
	Music::Load();

	gm.money = gm.defaultMoney;

	sm.LoadScene("Title");
}

void Game::Update()
{
	Input::Update();

	if (!is_mousePos_outsideWindow_)
		sm.currentScene->Update(); 

	if (Input::GetButtonDown(PAD_INPUT_9))
	{
		PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
		if (!is_mousePos_outsideWindow_)
		{
			//SetValidMousePointerWindowOutClientAreaMoveFlag(TRUE);
			is_mousePos_outsideWindow_ = true;
		}
		else
		{
			//SetValidMousePointerWindowOutClientAreaMoveFlag(FALSE);
			is_mousePos_outsideWindow_ = false;
		}
		return;
	}
}

void Game::Draw()
{
	sm.currentScene->Draw();
	if (is_mousePos_outsideWindow_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawString(Screen::width / 2 - 10, Screen::height / 2, "POUSE", gm.colorWhite);
	}
}
