#ifndef PRODUCTIONSECTIONBASE_H_
#define PRODUCTIONSECTIONBASE_H_

#include "GameManager.h"
#include "SceneManager.h"
#include <DxLib.h>

class ProductionSectionBase
{
public:
	GameManager& gm = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	ProductionSectionBase() = default;
	~ProductionSectionBase() = default;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	static std::vector<bool> canWeaponMake_;

protected:
	// ���탌�V�sGet�t���O
	static bool canWoodSword_;
	static bool canJawaSword_;
	static bool canEnriSword_;
	static bool canKeinSword_;
	static bool canShizukuSword_;
	static bool canSaintSword_;
	static bool canGodWoodSword_;

	static bool canStoneSword_;
	static bool canIronOreSword_;
	static bool canJadeSword_;
	static bool canDiamondSword_;
	static bool canCarbonadeSword_;
	static bool canOrichalcumSword_;
	static bool canGodStoneSword_;

	const int CsvSkipCell_ = 2;
	const int CsvTypeCheckFine_ = 5;
	const int CsvTypeCheck_ = 6;
	const int CsvNecessaryItem_ = 4;
	const int DrawMaxPouchSize_ = 42;
	const int lumberNum_ = 1;

	const int DetailWindowX_ = 600;
	const int DetailWindowY_ = 80;
	const int ItemNameX_ = 650;
	const int ItemNameY_ = 100;
	const int ItemQualityX_ = 900;
	const int ItemInfoX_ = 650;
	const int ItemInfoY_ = 200;

	static int cursorX_; // �J�[�\�����W
	static int cursorY_;
	static int prevCursorY_;

	static int selectIconNum_;
	static int scrollCount_;
	static int weaponID_;
	static int ItemType_; // �I���ł���A�C�e���̎��

	static bool weaponMakeAssert_;
	static bool itemDetail_;
	static bool cursorInit_;  // �J�[�\���̏�����
	static bool shouldWeaponMainCreate_; // ���C�������쐬�t���O
	static bool MainSlectOk_; // ���C�������I�������t���O
	static bool doAllFormat_;
	static bool shouldRetry_; // ���Ȃ����t���O
	static bool HandleSlectOk_; // �����蕔���I�������t���O
	static bool shouldCreate_; // �����t���O

	static std::vector<int> itemForWeaponMake_;		  // ���퐶���ɕK�v�ȃA�C�e�����ꎞ�I�ɕۊǂ���vector
	static std::vector<int> itemQualityForWeaponMake_;	  // ���퐶���ɕK�v�ȃA�C�e���̕i�����ꎞ�I�ɕۊǂ���vector
	static std::vector<int> ItemPosOnThePouch_;
	static std::vector<int> SelectItemPosOnThePouch_;
	static std::vector<int> PouchDrawErea_;
	static std::vector<int> NowDrawPosOnPouch_;

	void GetHandleForWeaponMake();
	void GetMainForWeaponMake(int ItemType);

	bool AlreadySecectItem(int ItemPosOnPouch);
};

#endif