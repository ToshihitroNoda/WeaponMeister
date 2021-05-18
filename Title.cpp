#include <DxLib.h>
#include "Title.h"
#include "Input.h"
#include "Image.h"

void Title::Init()
{

}

void Title::Final()
{
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
	DrawGraph(0, 0, Image::titleBack, TRUE);
	DrawGraph(TitleLogoBackX_, TitleLogoBackY_, Image::titleLogo, TRUE);

	if (count_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(DrawButtonX_, DrawButtonY_, Image::pressStartButton, TRUE);
	}
	count_++;
}