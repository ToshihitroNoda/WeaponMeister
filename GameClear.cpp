#include "GameClear.h"
#include "Input.h"
#include "ADVSimpleScript.h"

void GameClear::Init()
{
	gm.image.Load(tag);

	ADVSimpleScript::Init();

	filePath_ = ("Resource/Massege/Massege_GameClear.csv");

	ADVSimpleScript::Load(filePath_);
}

void GameClear::Final()
{
	gm.image.Final();
	sm.currentScene.reset();
}

void GameClear::Update()
{
	if (!massegeEnd_)
	{
		if (ADVSimpleScript::LoadEnd_)
		{
			if (Input::GetButtonDown(PAD_INPUT_1))
			{
				ADVSimpleScript::MassegeCount++;
				ADVSimpleScript::Update();
				Sleep(0.3f * 1000);			// 連打しても不具合が起こらないように0.3秒処理停止
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

void GameClear::Draw()
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
}