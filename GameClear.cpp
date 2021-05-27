#include "GameClear.h"
#include "Input.h"
#include "ADVSimpleScript.h"
#include "Music.h"
#include <sstream>

void GameClear::Init()
{
	gm.image.Load(tag);
	gm.money -= RentLastDay_;

	gm.scoreData.Load("Resource/Datas/ScoreData.csv");

	sold_weapon_         = gm.weapons.back();
	sold_weapon_quality_ = gm.weaponQuality.back();
	
	for (int i = CsvSkipCsell_; i < gm.scoreData[0].size(); i++)
	{
		if ((int)gm.scoreData[CsvWeaponIdCsll_][i] == sold_weapon_)
		{
			if (sold_weapon_quality_ <= (int)gm.scoreData[CsvQuality_1Cell_][i])
				evaluation_ = (int)gm.scoreData[CsvEvaluation_1Cell_][i];
			else if (sold_weapon_quality_ <= (int)gm.scoreData[CsvQuality_2Cell_][i])
				evaluation_ = (int)gm.scoreData[CsvEvaluation_2Cell_][i];
			else
				evaluation_ = (int)gm.scoreData[CsvEvaluation_3Cell_][i];
		}
	}

	ADVSimpleScript::Init();

	filePath_ = ("Resource/Massege/Massege_GameClear.csv");

	ADVSimpleScript::Load(filePath_);
}

void GameClear::Final()
{
	ADVSimpleScript::Final();
	gm.image.Final();
	sm.currentScene.reset();
}

void GameClear::Update()
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
				massegeEnd_ = true;
			}
		}
		ADVSimpleScript::Update();
	}
	else
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			remove("savedata.dat");
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

		DrawGraph(350, 200, gm.image.rank, TRUE);
		DrawGraph((Screen::width / 2) - 100, (Screen::height / 2) - 100, gm.image.scores[evaluation_], TRUE);
		DrawString(750, 500, "勇者に売った武器", gm.colorWhite);
		DrawGraph(920, 480, gm.image.itemIconWindow, TRUE);
		DrawGraph(920, 480, gm.image.weaponIcons[sold_weapon_], TRUE); 
		std::stringstream quality;
		quality << sold_weapon_quality_;
		DrawString(750, 550, ("品質 : " + quality.str()).c_str(), gm.colorWhite);
		std::stringstream money;
		money << gm.money;
		DrawString(950, 650, ("最終的な所持金 : " + money.str()).c_str(), gm.colorWhite);

	}
}