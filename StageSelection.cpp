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
	gm.mapData.LoadData("Resource/Datas/MapData.csv");

	if (Adv::day % NewStageAddDayDiameter_ == 0)
	{
		doNewStageAdd_ = true;
		mapCount++;
	}
	else
		doNewStageAdd_ = false;

	for (int i = 0; i < (unsigned)nowMapCount_.size(); i++)
	{
		if (mapCount >= nowMapCount_[i])
		{
			canMakeWeapon_ += KindofCanWeaponsMake_[i];
			for (int j = 0; j < alreadyTrueWapon_ + canMakeWeapon_; j++)
			{
				production.canWeaponMake_[j] = true;
				production.canWeaponMake_[j + production.canWeaponMake_.size() / 2] = true;
			}
			addMapList_[i] = true;
		}
	}

}

void StageSelection::Final()
{
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
			if (cursorX_ == mapIconPostions_[i] - CursorXDistMapX_ && cursorY_ == mapIconPostions_[i + (mapIconPostions_.size() / 2)] - CursorYDistMapY_)
			{
				stageNum = stageNums_[i];
			}
		}
		sm.LoadScene("Collection");
	}

	if (Input::GetButtonDown(PAD_INPUT_RIGHT))
	{
		for (int i = 0; i < (unsigned)nowMapCount_.size(); i++)
		{
			if (mapCount == nowMapCount_[i])
			{
				if (cursorX_ != mapIconPostions_[i + 1] - CursorXDistMapX_)
				{
					cursorX_ += MoveCursorDist;
				}
			}
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_LEFT))
	{
		for (int i = 0; i < (unsigned)nowMapCount_.size(); i++)
		{
			if (mapCount == nowMapCount_[i])
			{
				if (mapCount >= nowMapCount_[nowMapCount_.size() / 2])
				{
					if (cursorX_ != mapIconPostions_[3] - CursorXDistMapX_)
					{
						cursorX_ -= MoveCursorDist;
					}
				}
				if (cursorX_ != mapIconPostions_[0] - CursorXDistMapX_)
				{
					cursorX_ -= MoveCursorDist;
				}
			}
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_UP))
	{
		if (mapCount == 4)
		{
			if (cursorY_ == Map4IconPosY_)
			{
				cursorY_ = Map1IconPosY_;
				cursorX_ = Map1IconPosX_ - CursorXDistMapX_;
			}
		}
		else if (mapCount == 5)
		{
			if (cursorY_ == Map5IconPosY_)
			{
				cursorY_ = Map1IconPosY_;
				cursorX_ = Map1IconPosX_ - CursorXDistMapX_;
			}
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_DOWN))
	{
		if (mapCount == 4)
		{
			if (cursorY_ == Map1IconPosY_)
			{
				cursorY_ = Map4IconPosX_;
				cursorX_ = Map4IconPosY_ - CursorXDistMapX_;
			}
		}
		else if (mapCount == 5)
		{
			if (cursorY_ == Map1IconPosY_)
			{
				cursorY_ = Map4IconPosX_;
				cursorX_ = Map4IconPosY_ - CursorXDistMapX_;
			}
		}
	}
}

void StageSelection::Draw()
{
	DrawGraph(0, 0, Image::dayWindow, TRUE);
	DrawGraph(0, 0, Image::dayNum[Adv::day], TRUE);

	if (doNewStageAdd_)
	{
		DrawString(0, 60, "newStage!!", gm.colorWhite);
	}

	for (int i = 0; i < ((unsigned)mapIconPostions_.size() / 2) - 1; i++)
	{
		DrawGraph(mapIconPostions_[0], mapIconPostions_[mapIconPostions_.size() / 2], mapIcons_[i], TRUE);
		if (addMapList_[i])
		{
			DrawGraph(mapIconPostions_[i + 1], mapIconPostions_[(i + 1) + (mapIconPostions_.size() / 2)], mapIcons_[i], TRUE);
		}
	}

	DrawGraph(cursorX_, cursorY_, Image::mapCursor, TRUE);

	if (nowLoadingDraw_)
	{
		DrawBox(0, 0, Screen::Width, Screen::Height, gm.colorBrack, TRUE);
		DrawString(900, 600, "Now Loading...", gm.colorWhite);
		nextSceneLoad_ = true;
	}
}

