#include <DxLib.h>
#include "Title.h"
#include "Input.h"

void Title::Init()
{
	gm.image.Load(tag);
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