#include "StageSelection.h"

#include "Map.h"
#include "Production.h"
#include "Adv.h"
#include "Input.h"

Production production;
Adv adv;

void StageSelection::Init()
{
	gm.mapData.LoadData("Resource/Datas/MapData.csv");

	if (adv.day % NewStageAddDayDiameter_ == 0)
	{
		doNewStageAdd_ = true;
		mapCount_++;
	}
	else
		doNewStageAdd_ = false;

	for (int i = 0; i < (unsigned)nowMapCount_.size(); i++)
	{
		if (mapCount_ >= nowMapCount_[i])
		{
			canMakeWeapon_ += KindofCanWeaponsMake_[i];
			for (int j = 0; j < alreadtTrueWapon_ + canMakeWeapon_; j++)
			{
				production.canWeaponMake_[j] = true;
			}
			addMapList_[i] = true;
		}
	}

}

void StageSelection::Final()
{

}

void StageSelection::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		for (int i = 0; i < (unsigned)mapIconPostions_.size() / 2; i++)
		{
			if (cursorX_ == mapIconPostions_[i] && cursorY_ == mapIconPostions_[i + (mapIconPostions_.size() / 2)])
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
			if (mapCount_ == nowMapCount_[i])
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
			if (mapCount_ == nowMapCount_[i])
			{
				if (mapCount_ >= nowMapCount_[nowMapCount_.size() / 2])
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
		if (mapCount_ == 4)
		{
			if (cursorY_ == Map4IconPosY_)
			{
				cursorY_ = Map1IconPosY_;
				cursorX_ = Map1IconPosX_ - CursorXDistMapX_;
			}
		}
		else if (mapCount_ == 5)
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
		if (mapCount_ == 4)
		{
			if (cursorY_ == Map1IconPosY_)
			{
				cursorY_ = Map4IconPosX_;
				cursorX_ = Map4IconPosY_ - CursorXDistMapX_;
			}
		}
		else if (mapCount_ == 5)
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
	DrawGraph(0, 0, Image::dayNum[adv.day], TRUE);

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
}

