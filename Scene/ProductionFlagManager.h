#ifndef PRODUCTIONFLAGMANAGER_H_
#define PRODUCTIONFLAGMANAGER_H_

#include "ProductionSectionBase.h"

// Production�Ƀt���O����n������N���X
class ProductionFlagManager : ProductionSectionBase
{
public:
	ProductionFlagManager() = default;
	~ProductionFlagManager() = default;

	void Final()
	{
		weaponMakeAssert_         = weaponMakeAssert;
		itemDetail_               = itemDetail;
		cursorInit_               = cursorInit;  
		shouldWeaponMainCreate_   = shouldWeaponMainCreate; 
		MainSlectOk_              = MainSlectOk; 
		doAllFormat_              = doAllFormat;
		shouldRetry_              = shouldRetry; 
		HandleSlectOk_            = HandleSlectOk; 
		shouldCreate_             = shouldCreate;
		itemForWeaponMake_        = itemForWeaponMake;
		itemQualityForWeaponMake_ = itemQualityForWeaponMake;
		ItemPosOnThePouch_        = ItemPosOnThePouch;
		SelectItemPosOnThePouch_  = SelectItemPosOnThePouch;
		scrollCount_              = scrollCount;
	}

	void Update() override
	{
		weaponMakeAssert         = weaponMakeAssert_;
		itemDetail               = itemDetail_;
		cursorInit               = cursorInit_;  
		shouldWeaponMainCreate   = shouldWeaponMainCreate_; 
		MainSlectOk              = MainSlectOk_; 
		doAllFormat              = doAllFormat_;
		shouldRetry              = shouldRetry_; 
		HandleSlectOk            = HandleSlectOk_; 
		shouldCreate             = shouldCreate_;
		itemForWeaponMake        = itemForWeaponMake_;
		itemQualityForWeaponMake = itemQualityForWeaponMake_;
		ItemPosOnThePouch        = ItemPosOnThePouch_;
		SelectItemPosOnThePouch  = SelectItemPosOnThePouch_;
		scrollCount              = scrollCount_;
	}
	void Draw() override {}

	int scrollCount = 0;

	bool weaponMakeAssert = false;
	bool playErrorSound = false;
	bool itemDetail = false;
	bool cursorInit = true;  // �J�[�\���̏�����
	bool shouldWeaponMainCreate = false; // ���C�������쐬�t���O
	bool MainSlectOk = false; // ���C�������I�������t���O
	bool doAllFormat = false;
	bool MakeEnd = false;
	bool shouldRetry = false; // ���Ȃ����t���O
	bool HandleSlectOk = false; // �����蕔���I�������t���O
	bool animationEnd = false;
	bool shouldCreate = false; // �����t���O

	std::vector<int> itemForWeaponMake;		  // ���퐶���ɕK�v�ȃA�C�e�����ꎞ�I�ɕۊǂ���vector
	std::vector<int> itemQualityForWeaponMake;	  // ���퐶���ɕK�v�ȃA�C�e���̕i�����ꎞ�I�ɕۊǂ���vector
	std::vector<int> ItemPosOnThePouch;
	std::vector<int> SelectItemPosOnThePouch;
};

#endif