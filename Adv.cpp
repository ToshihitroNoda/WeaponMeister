#include "Adv.h"
#include "Input.h"
#include "Image.h"

void Adv::Init()
{
	day++;

	std::stringstream ss;
	ss << day;
	gm.massegeData.Load("Resource/Massege/Massege_" + ss.str() + ".csv");
}

void Adv::Final()
{

}

void Adv::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_2))
	{
		sm.LoadScene("StageSelection");
	}
}

void Adv::Draw()
{
	DrawGraph(WindowX_, WindowY_, Image::textWindow, TRUE);

	if (IconFlashCount_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(CursorX_, CursorY_, Image::textCursor, TRUE);
	}
	IconFlashCount_++;
}
