#ifndef STAGESELECTION_H_
#define STAGESELECTION_H_

#include <string>
#include <stdio.h>

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Map.h"
#include "DataCsv.h"
#include "Image.h"

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

	int stageNum   = 0;

private:

	int cursorX_	= 120;
	int cursorY_	= 300;
	int mapCount_	= 1;
	int canMakeWeapon_ = 0;

	bool addMap2_			= false;
	bool addMap3_			= false;
	bool addMap4_			= false;
	bool addMap5_			= false;
	bool doNewStageAdd_		= false;
	bool nextSceneLoad_		= false;
	bool nowLoadingDraw_	= false;

	const int NewStageAddDayDiameter_ = 3; // これで割り切れる日に新しいステージ追加
	const int alreadtTrueWapon_ = 2; // 既に作れるようになっている武器は配列の最初から2つ目まで

	const int Map1IconPosX_ = 200;
	const int Map1IconPosY_ = 300;
	const int Map2IconPosX_ = 600;
	const int Map2IconPosY_ = 300;
	const int Map3IconPosX_ = 1000;
	const int Map3IconPosY_ = 300;
	const int Map4IconPosX_ = 400;
	const int Map4IconPosY_ = 500;
	const int Map5IconPosX_ = 800;
	const int Map5IconPosY_ = 500;

	const int CursorXDistMapX_ = 80;
	const int CursorYDistMapY_ = 0;

	const int MoveCursorDist   = 400;

	const int CsvSkipCell_	   = 2;

	std::vector<bool> addMapList_{ addMap2_, addMap3_, addMap4_, addMap5_ };

	std::vector<int>  nowMapCount_{ 2, 3, 4, 5 };
	std::vector<int>  KindofCanWeaponsMake_{ 2, 4, 2, 2 };
	std::vector<int>  stageNums_{ 0, 1, 2, 3, 4 };
	std::vector<int>  mapIcons_{ Image::mapIcon, Image::mapIcon, Image::mapIcon, Image::mapIcon, Image::mapIcon, };
	std::vector<int>  mapIconPostions_
		{ Map1IconPosX_, Map2IconPosX_, 
		  Map3IconPosX_, Map4IconPosX_, 
		  Map5IconPosX_, 
		  Map1IconPosY_, Map2IconPosY_,
		  Map3IconPosY_, Map4IconPosY_,
		  Map5IconPosY_ };

};

#endif

