#include "Adv.h"
#include "../MyLib/Input.h"
#include "../MyLib/ADVSimpleScript.h"
#include "../Music.h"

int Adv::day = 0;

void Adv::Init()
{
	gm.image.Load(tag);
	day++;

	ADVSimpleScript::Init();

	std::stringstream ss;
	ss << day;
	filePath_ = ("Resource/Message/Message_" + ss.str() + ".csv");

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
		if (Input::GetButtonDown(PAD_INPUT_1) && !autoMode_ && !skipMode_)
		{
			ADVSimpleScript::MessageCount++;
		}
		if (Input::GetButtonDown(PAD_INPUT_2) && !skipMode_)
		{
			if (!autoMode_)
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				autoMode_ = true;
			}
			else
			{
				PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
				autoMode_ = false;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_3) && !autoMode_)
		{
			if (!skipMode_)
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				skipMode_ = true;
			}
			else
			{
				PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
				skipMode_ = false;
			}
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
			isDead = true;
		}
	}
	ADVSimpleScript::Update();
	IconFlashCount_++;
}

void Adv::Change()
{
	sm.LoadScene("StageSelection");
}

void Adv::Draw()
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
	DrawString(OptionMenuX_, OptionMenuY_, "Xキー : オートモード  ,  Cキー : スキップモード", gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);

	if (IconFlashCount_ % Divisor_ < DrawFlashTiming_)
	{
		DrawGraph(CursorX_, CursorY_, gm.image.textCursor, TRUE);
	}
}
