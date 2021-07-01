#include "GameOver.h"
#include "../MyLib/Input.h"
#include "../MyLib/ADVSimpleScript.h"
#include "Adv.h"
#include "../Music.h"

#include <sstream>

void GameOver::Init()
{
	gm.image.Load(tag);

	ADVSimpleScript::Init();

	filePath_ = ("Resource/Message/Message_GameOver.csv");

	ADVSimpleScript::Load(filePath_);
}

void GameOver::Final()
{
	ADVSimpleScript::Final();
	gm.image.Final();
	sm.currentScene.reset();
}

void GameOver::Update()
{
	if (!messageEnd_)
	{
		if (ADVSimpleScript::LoadEnd_)
		{
			if (Input::GetButtonDown(PAD_INPUT_1) && !autoMode_ && !skipMode_)
			{
				ADVSimpleScript::MessageCount++;
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
					ADVSimpleScript::MessageCount++;
					autoCounter_ = 0;
				}
				autoCounter_++;
			}
			if (skipMode_)
			{
				if (skipCounter_ >= SkipSpeed_)
				{
					ADVSimpleScript::MessageCount++;
					skipCounter_ = 0;
				}
				skipCounter_++;
			}

			if (ADVSimpleScript::MessageCount >= ADVSimpleScript::messageList.size())
			{
				messageEnd_ = true;
			}
		}
		ADVSimpleScript::Update();
	}
	else
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			isDead = true;
		}
	}
}

void GameOver::Change()
{
	remove("savedata.dat");
	sm.LoadScene("Title");
}

void GameOver::Draw()
{
	if (!messageEnd_)
	{
		ADVSimpleScript::ImageDraw();

		DrawGraph(WindowX_, WindowY_, gm.image.textWindow, TRUE);

		if (ADVSimpleScript::LoadEnd_)
			ADVSimpleScript::MessageDraw(gm.colorWhite);

		if (autoMode_)
			DrawBox(865, 690, 975, 705, gm.colorBlue, TRUE);
		if (skipMode_)
			DrawBox(1085, 690, 1205, 705, gm.colorBlue, TRUE);

		SetFontSize(15);
		DrawString(OptionMenuX_, OptionMenuY_, "X�L�[ : �I�[�g���[�h  ,  C�L�[ : �X�L�b�v���[�h", gm.colorWhite);
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
		DrawString(TitleX_, TitleY_, "�c�Ɗ��� : ", gm.colorWhite);
		std::stringstream ss;
		ss << Adv::day;
		DrawString(DayX_, DayY_, (ss.str() + " �� ").c_str(), gm.colorWhite);
		DrawString(NextMessageX_, NextMessageY_, "Z�L�[�ŏI��", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}
}
