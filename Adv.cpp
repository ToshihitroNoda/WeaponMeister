#include "Adv.h"
#include "Input.h"
#include "Image.h"
#include "ADVSimpleScript.h"

int Adv::day = 0;

void Adv::Init()
{
	day++;

	ADVSimpleScript::Init();

	std::stringstream ss;
	ss << day;
	filePath_ = ("Resource/Massege/Massege_" + ss.str() + ".csv");

	ADVSimpleScript::Load(filePath_);
}


void Adv::Final()
{

}

void Adv::Update()
{
	if (ADVSimpleScript::LoadEnd_)
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			ADVSimpleScript::MassegeCount++;
		}

		if (ADVSimpleScript::MassegeCount >= ADVSimpleScript::massegeList.size())
		{
			sm.LoadScene("StageSelection");
		}
	}
	ADVSimpleScript::Update();
}

void Adv::Draw()
{
	ADVSimpleScript::ImageDraw();

	DrawGraph(WindowX_, WindowY_, Image::textWindow, TRUE);

	if (ADVSimpleScript::LoadEnd_)
		ADVSimpleScript::MassegeDraw(gm.colorWhite);

	if (IconFlashCount_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(CursorX_, CursorY_, Image::textCursor, TRUE);
	}
	IconFlashCount_++;
}
