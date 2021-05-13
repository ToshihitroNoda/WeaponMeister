#include "GameOver.h"
#include "Input.h"

void GameOver::Init()
{

}

void GameOver::Final()
{

}

void GameOver::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		sm.LoadScene("Title");
	}
}

void GameOver::Draw()
{
	DrawString(0, 0, "GameOver", gm.colorWhite);
}
