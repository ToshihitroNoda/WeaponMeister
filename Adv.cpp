#include "Adv.h"
#include "Input.h"
#include "Image.h"
#include "ADVSimpleScript.h"

int Adv::day = 0;

void Adv::Init()
{
	day++;

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
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		ADVSimpleScript::MassegeCount_++;
	}

	if (ADVSimpleScript::MassegeCount_ >= ADVSimpleScript::massegeList_.size())
	{
		sm.LoadScene("StageSelection");
	}

	ADVSimpleScript::Update();
}

void Adv::Draw()
{
	ADVSimpleScript::ImageDraw();

	DrawGraph(WindowX_, WindowY_, Image::textWindow, TRUE);

	ADVSimpleScript::MassegeDraw(gm.colorWhite);

	if (IconFlashCount_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(CursorX_, CursorY_, Image::textCursor, TRUE);
	}
	IconFlashCount_++;
}
