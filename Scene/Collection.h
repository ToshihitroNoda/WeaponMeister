#ifndef COLLECTION_H_
#define COLLECTION_H_

#include "Scene.h"
#include "SceneManager.h"
#include "../GameManager.h"
#include "StageSelection.h"
#include "../MyLib/DataCsv.h"


class Collection : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	Collection() : Scene()
	{
		this->tag = "Collection";
	}
	~Collection() = default;

	void Init() override;
	void Final() override;
	void Update() override;
	void Change() override;
	void Draw() override;

private:
	void ItemGet();
	void MoveCursor();
	void Collide();

	const int DrawGetItemCountMax_     = 120;
	const int DrawGetItemCountMinimum_ = 5;

	const int DrawMaxPouchSize_ = 42;

	const int WatchX_ = 1158;
	const int WatchY_ = 122;

	const int DrawGetItemX_       = 700;
	const int DrawGetItemY_       = 300;
	const int DrawGetItemX_Width_ = 72;

	const int WindowX_          = 60;
	const int WindowY_          = 80;
	const int WindowX_CellSize_ = 6;
	const int WindowY_CellSize_ = 7;
	const int WindowCellSize_X_ = 72;
	const int WindowCellSize_Y_ = 73;

	const int DetailWindowX_ = 600;
	const int DetailWindowY_ = 80;
	const int ItemNameX_     = 650;
	const int ItemNameY_     = 100;
	const int ItemQualityX_  = 900;
	const int ItemInfoX_     = 650;
	const int ItemInfoY_     = 200;

	const int CursorX_Min_ItemSelect_               = 84;
	const int CursorY_Min_ItemSelect_               = 139;
	const int CursorX_Max_ItemSelect_               = 444;
	const int CursorY_Max_ItemSelect_               = 577;
	const int CursorX_MoveVerticalWidth_ItemSelect_ = 72;
	const int CursorY_MoveVerticalWidth_ItemSelect_ = 73;
	const int WaponID_ByLineBreak_ItemSelect_       = 6;

	const int CsvSkipCell_   = 2;
	const int CsvItemID_     = 2;
	const int CsvCanGetMap1_ = 3;
	const int CsvCanGetMap2_ = 4;

	const int DrawPouchSizeX_ = 450;
	const int DrawPouchSizeY_ = 100;

	const int OptionMenuX_      = 790;
	const int OptionMenuY_      = 705;
	const int OptionMenuPouchX_ = 900;
	const int OptionMenuPouchY_ = 705;

	int getItem_                        = 0;  // ��ɓ��ꂽ�A�C�e��ID
	int getItemCount_                   = 0;  // ��x�Ɏ�ɓ������A�C�e����
	int getItemCountMax_                = 5;  // ��x�Ɏ�ɓ������A�C�e�����̍ő�l
	int qualityStorage_                 = 0;  // �i���ꎞ�ۊǕϐ�
	int getItemDrawCounter_             = 0;
	int itemX_                          = 84; // �A�C�e���A�C�R�����W
	int itemY_                          = 141;
	int cursorX_                        = CursorX_Min_ItemSelect_;	// �J�[�\�����W
	int cursorY_                        = CursorY_Min_ItemSelect_;
	int selectIconNum_                  = 0;
	int scrollCount_                    = 0;
	int startCount_                     = 120;
	int endCount_                       = 120;
	int collectTimer_                   = 7200;	 // �̎掞�ԁB2��
	int backGroundHandle_               = 0;
	int operationDescriptionMessageNum_ = 0;

	float watchPointerAngle_ = 0.0f; // ���v�̐j�̊p�x�B1�t���[����+=0.05f�����2���ň��
	float plusPointerAngle_  = 0.05f;

	bool getItemFlg_                    = false; // �A�C�e���Q�b�g�t���O
	bool menuOpen_                      = false;
	bool menuInit_                      = false;
	bool collectionEnd_                 = false;
	bool playStartSound_                = false;
	bool playEndSound_                  = false;
	bool is_Operation_Description_Been_ = false;

	std::vector<int> possibilityToGetItem_;
	std::vector<int> DrawGetItem_;
	std::vector<int> PouchDrawErea_;

	std::string description_[6]
	{ "����ł͑����̎���n�߂Ă����܂��傤�I",
	  "�L�[�{�[�h��WASD�ňړ��A�}�E�X�ŃJ�������삪�s���܂��B",
	  "��ʉE��̎��v�����������̎�I���ƂȂ�܂��B����܂łɑ����̑f�ނ��W�߂܂��傤�B",
	  "�}�b�v��̔��������Ă���I�u�W�F�N�g�ɋ߂Â��Ƒf�ނ��̎�ł��܂��B",
	  "C�L�[���������Ƃō̎�ς݂̃A�C�e�����m�F���邱�Ƃ��ł��܂��B",
	  "�ȏオ�����ɂȂ�܂��B����ł͍̎���n�߂Ă݂܂��傤�I"
	};
};

#endif

