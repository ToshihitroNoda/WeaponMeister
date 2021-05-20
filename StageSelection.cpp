#include "StageSelection.h"

#include "Map.h"
#include "Production.h"
#include "Adv.h"
#include "Input.h"
#include "Screen.h"

Production production;

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

	for (int i = 0; i < nowMapCount_.size(); i++)
	{
		if (mapCount >= nowMapCount_[i])
		{
			canMakeWeapon_ += KindofCanWeaponsMake_[i];
			for (int j = 0; j < alreadyTrueWapon_ + canMakeWeapon_; j++)
			{
				Production::canWeaponMake_[j] = true;
				Production::canWeaponMake_[j + Production::canWeaponMake_.size() / 2] = true;
			}
			addMapList_[i] = true;
		}
	}

	mapIcons_.resize(5);
	mapIcons_ = { gm.image.mapIcon_1, gm.image.mapIcon_2, gm.image.mapIcon_3, gm.image.mapIcon_4, gm.image.mapIcon_5 };
}

void StageSelection::Final()
{
	gm.image.Final();
	sm.currentScene.reset();
}

void StageSelection::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
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
			cursorY_ = Map1IconPosY_;
			cursorX_ = Map1IconPosX_;

		}
	}
	if (Input::GetButtonDown(PAD_INPUT_DOWN))
	{
		if (mapCount > 3)
		{
			if (cursorY_ < Map5IconPosY_)
			{
				cursorY_ = Map4IconPosY_;
				cursorX_ = Map4IconPosX_;
			}
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

	DrawGraph(0, 0, gm.image.dayWindow, TRUE);
	DrawGraph(0, 0, gm.image.dayNum[Adv::day], TRUE);

	DrawGraph(cursorX_, cursorY_, gm.image.mapCursor, TRUE);

	if (nowLoadingDraw_)
	{
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		DrawString(900, 600, "Now Loading...", gm.colorWhite);
		nextSceneLoad_ = true;
	}
}

