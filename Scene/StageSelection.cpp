#include "StageSelection.h"

#include "Map.h"
#include "ProductionSectionBase.h"
#include "Adv.h"
#include "Input.h"
#include "Screen.h"
#include "Music.h"

int StageSelection::mapCount = 1;
int StageSelection::stageNum = 0;

void StageSelection::Init()
{
	gm.image.Load(tag);

	gm.mapData.LoadData("Resource/Datas/MapData.csv");

	if (Adv::day % NewStageAddDayDiameter_ == 0)
	{
		doNewStageAdd_ = true;
		mapCount++;
	}
	else
		doNewStageAdd_ = false;

	if (Adv::day != 1)
		is_Operation_Description_Been_ = true;

	for (int i = 0; i < nowMapCount_.size(); i++)
	{
		if (mapCount >= nowMapCount_[i])
		{
			canMakeWeapon_ += KindofCanWeaponsMake_[i];
			for (int j = 0; j < alreadyTrueWapon_ + canMakeWeapon_; j++)
			{
				ProductionSectionBase::canWeaponMake[ProductionSectionBase::canWeaponMakeKeys[j]] = true;
				ProductionSectionBase::canWeaponMake[ProductionSectionBase::canWeaponMakeKeys[j + 7]] = true;
			}
			addMapList_[i] = true;
		}
	}

	mapIcons_.resize(5);
	mapIcons_ = { gm.image.mapIcon_1, gm.image.mapIcon_2, gm.image.mapIcon_3, gm.image.mapIcon_4, gm.image.mapIcon_5 };

	attachIndex_ = MV1AttachAnim(gm.image.Player, 2, -1, FALSE);
	totalTime_   = MV1GetAttachAnimTotalTime(gm.image.Player, attachIndex_);
	playTime_    = 0.0f;
	MV1SetAttachAnimTime(gm.image.Player, attachIndex_, playTime_);

	PlaySoundMem(Music::stageselection_BGM, DX_PLAYTYPE_LOOP);
}

void StageSelection::Final()
{
	StopSoundMem(Music::stageselection_BGM);
	gm.image.Final();
	sm.currentScene.reset();
}

void StageSelection::Update()
{
	playTime_ += addPlayTime_;

	if (playTime_ >= totalTime_)
	{
		playTime_ = 0.0f;
	}
	MV1SetAttachAnimTime(gm.image.Player, attachIndex_, playTime_);

	if (is_Operation_Description_Been_)
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			nowLoadingDraw_ = true;
		}
		if (nextSceneLoad_)
		{
			for (int i = 0; i < mapIconPostions_.size() / 2; i++)
			{
				if (cursorX_ == mapIconPostions_[i])
				{
					stageNum = stageNums_[i];
				}
			}
			sm.LoadScene("Collection");
		}

		if (Input::GetButtonDown(PAD_INPUT_RIGHT))
		{
			if (mapCount > 1)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				for (int i = 0; i < mapIconPostions_.size() / 2; i++)
				{
					if (cursorX_ == mapIconPostions_[i]) // 今どのマップ選んでるか
					{
						if (mapIconPostions_[i + 1] > mapIconPostions_[i]) // 今選んでるマップより右にあるのを選択しようとしてたら
						{
							if (addMapList_[i])
							{
								cursorX_ = mapIconPostions_[i + 1];
								break;
							}
						}
					}
				}
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_LEFT))
		{
			if (mapCount > 1 && cursorX_ != mapIconPostions_[0] && cursorX_ != mapIconPostions_[3])
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				for (int i = 0; i < mapIconPostions_.size() / 2; i++)
				{
					if (cursorX_ == mapIconPostions_[i])	// 今どのマップ選んでるか
					{
						if (mapIconPostions_[i - 1] < mapIconPostions_[i]) // 今選んでるマップより左にあるのを選択しようとしてたら
							cursorX_ = mapIconPostions_[i - 1];
					}
				}
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_UP))
		{
			if (cursorX_ == mapIconPostions_[3] || cursorX_ == mapIconPostions_[4])
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorY_ = Map1IconPosY_;
				cursorX_ = Map1IconPosX_;

			}
		}
		if (Input::GetButtonDown(PAD_INPUT_DOWN))
		{
			if (mapCount > 3 && cursorY_ < Map5IconPosY_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorY_ = Map4IconPosY_;
				cursorX_ = Map4IconPosX_;

			}
		}
	}
	else
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			if (operationDescriptionMassegeNum_ < sizeof(description_) / sizeof(*description_) - 1)
				operationDescriptionMassegeNum_++;
			else
				is_Operation_Description_Been_ = true;
		}
	}
}

void StageSelection::Draw()
{
	DrawGraph(0, 0, gm.image.worldMap, TRUE);

	for (int i = 0; i < ((unsigned)mapIconPostions_.size() / 2) - 1; i++)
	{
		DrawGraph(mapIconPostions_[0], mapIconPostions_[mapIconPostions_.size() / 2], mapIcons_[0], TRUE);
		if (addMapList_[i])
		{
			DrawGraph(mapIconPostions_[i + 1], mapIconPostions_[(i + 1) + (mapIconPostions_.size() / 2)], mapIcons_[i + 1], TRUE);
		}
	}

	if (!nowLoadingDraw_)
	{
		MV1SetPosition(gm.image.Player, VGet(cursorX_ + 100, -cursorY_ + 520, 0));
		MV1SetScale(gm.image.Player, VGet(0.8f, 0.8f, 0.8f));
		MV1DrawModel(gm.image.Player);

		DrawGraph(0, 0, gm.image.dayWindow, TRUE);
		DrawGraph(0, 0, gm.image.dayNum[Adv::day], TRUE);

		SetFontSize(15);
		DrawString(OptionMenuX_, OptionMenuY_, "←↑→↓ : カーソル移動　,　Zキー : 選択", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}

	if (nowLoadingDraw_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawString(900, 600, "Now Loading...", gm.colorWhite);
		nextSceneLoad_ = true;
	}

	if (!is_Operation_Description_Been_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		std::string drawNextDescription = "Zキーで次へ";
		int DrawWidthUnder = GetDrawStringWidth(drawNextDescription.c_str(), -1);
		DrawString((Screen::width - DrawWidthUnder) / 2, (Screen::height - (Screen::height / 4) + 30), drawNextDescription.c_str(), gm.colorWhite);
		std::string drawMassege = description_[operationDescriptionMassegeNum_];
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}
}

