#include "GameOver.h"
#include "Input.h"
#include "ADVSimpleScript.h"
#include "Adv.h"

#include <sstream>

void GameOver::Init()
{
	gm.image.Load(tag);

	ADVSimpleScript::Init();

	filePath_ = ("Resource/Massege/Massege_GameOver.csv");

	ADVSimpleScript::Load(filePath_);
}

void GameOver::Final()
{
	gm.image.Final();
	sm.currentScene.reset();
}

void GameOver::Update()
{
	if (!massegeEnd_)
	{
		if (ADVSimpleScript::LoadEnd_)
		{
			if (Input::GetButtonDown(PAD_INPUT_1))
			{
				ADVSimpleScript::MassegeCount++;
			}

			if (ADVSimpleScript::MassegeCount >= ADVSimpleScript::massegeList.size())
			{
				massegeEnd_ = true;
			}
		}
		ADVSimpleScript::Update();
	}
	else
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			sm.LoadScene("Title");
		}
	}
}

void GameOver::Draw()
{
	if (!massegeEnd_)
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
	else
	{
		DrawGraph(0, 0, gm.image.reportBack, TRUE);
		SetFontSize(FontSize_);
		DrawString(TitleX_, TitleY_, "‰c‹ÆŠúŠÔ : ", gm.colorWhite);
		std::stringstream ss;
		ss << Adv::day;
		DrawString(DayX_, DayY_, (ss.str() + " “ú ").c_str(), gm.colorWhite);
		DrawString(NextMassegeX_, NextMassegeY_, "ZƒL[‚ÅI—¹", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}
}
