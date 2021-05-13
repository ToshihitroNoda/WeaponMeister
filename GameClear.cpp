#include "GameClear.h"
#include "Input.h"

void GameClear::Init()
{

}

void GameClear::Final()
{

}

void GameClear::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		sm.LoadScene("Title");
	}
}

void GameClear::Draw()
{
	DrawString(0, 0, "GameClear", gm.colorWhite);
}