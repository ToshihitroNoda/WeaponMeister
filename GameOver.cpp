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
			if (Input::GetButtonDown(PAD_INPUT_1) && !autoMode_ && !skipMode_)
			{
				ADVSimpleScript::MassegeCount++;
			}
			if (Input::GetButtonDown(PAD_INPUT_2) && !skipMode_)
			{
				if (!autoMode_)
					autoMode_ = true;
				else
					autoMode_ = false;
			}
			if (Input::GetButtonDown(PAD_INPUT_3) && !autoMode_)
			{
				if (!skipMode_)
					skipMode_ = true;
				else
					skipMode_ = false;
			}

			if (autoMode_)
			{
				if (autoCounter_ >= AutoSpeed_)
				{
					ADVSimpleScript::MassegeCount++;
					autoCounter_ = 0;
				}
				autoCounter_++;
			}
			if (skipMode_)
			{
				if (skipCounter_ >= SkipSpeed_)
				{
					ADVSimpleScript::MassegeCount++;
					skipCounter_ = 0;
				}
				skipCounter_++;
			}

			if (ADVSimpleScript::MassegeCount >= ADVSimpleScript::massegeList.size())
			{
				sm.LoadScene("StageSelection");
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

		if (autoMode_)
			DrawBox(865, 690, 975, 705, gm.colorBlue, TRUE);
		if (skipMode_)
			DrawBox(1085, 690, 1205, 705, gm.colorBlue, TRUE);

		SetFontSize(15);
		DrawString(OptionMenuX_, OptionMenuY_, "Xキー : オートモード  ,  Cキー : スキップモード", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);

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
		DrawString(TitleX_, TitleY_, "営業期間 : ", gm.colorWhite);
		std::stringstream ss;
		ss << Adv::day;
		DrawString(DayX_, DayY_, (ss.str() + " 日 ").c_str(), gm.colorWhite);
		DrawString(NextMassegeX_, NextMassegeY_, "Zキーで終了", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}
}
