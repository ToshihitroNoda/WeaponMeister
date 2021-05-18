#include "Adv.h"
#include "Input.h"
#include "ADVSimpleScript.h"

int Adv::day = 0;

void Adv::Init()
{
	gm.image.Load(tag);
	day++;

	ADVSimpleScript::Init();

	std::stringstream ss;
	ss << day;
	filePath_ = ("Resource/Massege/Massege_" + ss.str() + ".csv");

	ADVSimpleScript::Load(filePath_);
}


void Adv::Final()
{
	ADVSimpleScript::Final();
	gm.image.Final();
	sm.currentScene.reset();
}

void Adv::Update()
{
	if (ADVSimpleScript::LoadEnd_)
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			ADVSimpleScript::MassegeCount++;
			ADVSimpleScript::Update();
			Sleep(0.3f * 1000);			// ˜A‘Å‚µ‚Ä‚à•s‹ï‡‚ª‹N‚±‚ç‚È‚¢‚æ‚¤‚É0.3•bˆ—’âŽ~
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

	DrawGraph(WindowX_, WindowY_, gm.image.textWindow, TRUE);

	if (ADVSimpleScript::LoadEnd_)
		ADVSimpleScript::MassegeDraw(gm.colorWhite);

	if (IconFlashCount_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(CursorX_, CursorY_, gm.image.textCursor, TRUE);
	}
	IconFlashCount_++;
}
