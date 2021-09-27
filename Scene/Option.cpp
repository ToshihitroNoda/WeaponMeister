#include "Option.h"
#include "../MyLib/Input.h"

void Option::Init()
{
	gm.image.Load(tag);
	if (gm.cameraReverseY == 1)	cursorX = 663;
	else cursorX = 590;
}

void Option::Final()
{
}

void Option::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_2))
	{
		isDead = true;
	}
	if (Input::GetButtonDown(PAD_INPUT_RIGHT) && cursorX != 663)
	{
		gm.cameraReverseY = 1;
	}
	else if (Input::GetButtonDown(PAD_INPUT_LEFT) && cursorX != 590)
	{
		gm.cameraReverseY = -1;
	}
	if (gm.cameraReverseY == 1)	cursorX = 663;
	else cursorX = 590;
}

void Option::Change()
{
	sm.LoadScene("MainMenu");
}

void Option::Draw()
{
	DrawGraph(0, 0, gm.image.mainmenuBack, TRUE);
	DrawBox(cursorX, 300, cursorX + 50, 315, gm.colorGray, TRUE);
	DrawString(400, 300, "カメラ左右反転　　　　　ON　　　OFF", gm.colorWhite);
	DrawString(1000, 700, "Xキー : メニューへ戻る", gm.colorWhite);
}
