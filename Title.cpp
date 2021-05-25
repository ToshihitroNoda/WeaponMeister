#include <DxLib.h>
#include "Title.h"
#include "Input.h"
#include "Music.h"

void Title::Init()
{
	gm.image.Load(tag);
	PlaySoundMem(Music::op, DX_PLAYTYPE_LOOP);
}

void Title::Final()
{
	gm.image.Final();
	sm.currentScene.reset();
}

void Title::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
		sm.LoadScene("MainMenu");
	}
}

void Title::Draw()
{
	DrawGraph(0, 0, gm.image.titleBack, TRUE);
	DrawGraph(TitleLogoBackX_, TitleLogoBackY_, gm.image.titleLogo, TRUE);

	if (count_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(DrawButtonX_, DrawButtonY_, gm.image.pressStartButton, TRUE);
	}
	count_++;
}