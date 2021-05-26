#ifndef STAGESELECTION_H_
#define STAGESELECTION_H_

#include <string>
#include <stdio.h>

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Map.h"
#include "DataCsv.h"

class StageSelection : public Scene
{
public:
	GameManager&  gm = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	StageSelection() : Scene()
	{
		this->tag = "StageSelection";
	}

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

	static int stageNum;
	static int mapCount;

private:
	const int Map1IconPosX_ = 200;
	const int Map1IconPosY_ = 130;
	const int Map2IconPosX_ = 600;
	const int Map2IconPosY_ = 160;
	const int Map3IconPosX_ = 1000;
	const int Map3IconPosY_ = 160;
	const int Map4IconPosX_ = 360;
	const int Map4IconPosY_ = 440;
	const int Map5IconPosX_ = 800;
	const int Map5IconPosY_ = 360;

	const int NewStageAddDayDiameter_ = 3; // ����Ŋ���؂����ɐV�����X�e�[�W�ǉ�
	const int alreadyTrueWapon_       = 2; // ���ɍ���悤�ɂȂ��Ă��镐��͔z��̍ŏ�����2�ڂ܂�

	const int CursorXDistMapX_ = 80;
	const int CursorYDistMapY_ = 0;

	const int MoveCursorDist = 400;

	const int CsvSkipCell_ = 2;

	int cursorX_	= Map1IconPosX_;
	int cursorY_	= Map1IconPosY_;
	int canMakeWeapon_ = 0;
	int operationDescriptionMassegeNum_ = 0;

	int attachIndex_ = 0;
	float totalTime_ = 0.0f;
	float playTime_ = 0.0f;
	float addPlayTime_ = 0.07f;

	bool addMap2_			= false;
	bool addMap3_			= false;
	bool addMap4_			= false;
	bool addMap5_			= false;
	bool doNewStageAdd_		= false;
	bool nextSceneLoad_		= false;
	bool nowLoadingDraw_	= false;

	bool is_Operation_Description_Been_ = false;

	std::vector<bool> addMapList_{ addMap2_, addMap3_, addMap4_, addMap5_ };

	std::vector<int>  nowMapCount_{ 2, 3, 4, 5 };
	std::vector<int>  KindofCanWeaponsMake_{ 1, 2, 1, 1 };
	std::vector<int>  stageNums_{ 1, 2, 3, 4, 5 };
	std::vector<int>  mapIcons_;
	std::vector<int>  mapIconPostions_
		{ Map1IconPosX_, Map2IconPosX_, 
		  Map3IconPosX_, Map4IconPosX_, 
		  Map5IconPosX_, 
		  Map1IconPosY_, Map2IconPosY_,
		  Map3IconPosY_, Map4IconPosY_,
		  Map5IconPosY_ };

	std::string description_[6]
	{ "�܂��͑f�ނ̍̎�ɏo�����܂��傤�I",
	  "���L�[�ŏo������̎�n��I�ׂ܂��B",
	  "�o������̎�n�����܂�����Z�L�[�ō̎�ɍs���܂��B",
	  "����1�ӏ������s����̎�n������܂��񂪁A",
	  "���ɂ����d�˂�ƍs����̎�n�������Ă����ł��傤�B",
	  "�ȏオ�����ɂȂ�܂��B����ł͍̎�ɏo�����܂��傤�I"
	};
};

#endif

