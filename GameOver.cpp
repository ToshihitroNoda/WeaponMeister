#include "GameOver.h"
#include "Input.h"
#include "Image.h"
#include "ADVSimpleScript.h"
#include "Adv.h"

#include <sstream>

void GameOver::Init()
{
	ADVSimpleScript::Init();

	filePath_ = ("Resource/Massege/Massege_GameOver.csv");

	ADVSimpleScript::Load(filePath_);
}

void GameOver::Final()
{
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
				ADVSimpleScript::Update();
				Sleep(0.3f * 1000);			// �A�ł��Ă��s����N����Ȃ��悤��0.3�b������~
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

		DrawGraph(WindowX_, WindowY_, Image::textWindow, TRUE);

		if (ADVSimpleScript::LoadEnd_)
			ADVSimpleScript::MassegeDraw(gm.colorWhite);

		if (IconFlashCount_ % Divisor_ < DrawFlashTiming_)
		{
			DrawGraph(CursorX_, CursorY_, Image::textCursor, TRUE);
		}
		IconFlashCount_++;
	}
	else
	{
		SetFontSize(FontSize_);
		DrawString(TitleX_, TitleY_, "�c�Ɗ��� : ", gm.colorWhite);
		std::stringstream ss;
		ss << Adv::day;
		DrawString(DayX_,DayY_,(ss.str() + " �� ").c_str(), gm.colorWhite);
		DrawString(NextMassegeX_, NextMassegeY_, "Z�L�[�ŏI��", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}
}
