#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "DataCsv.h"
#include "Image.h"
#include "Screen.h"

class Production : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance(); // �Q�[���}�l�[�W���[�ւ̎Q��
	SceneManager& sm = SceneManager::GetInstance(); // �V�[���}�l�[�W���[�ւ̎Q��

	Production() : Scene() // �R���X�g���N�^
	{
		this->tag = "Production";
	}
	~Production() {};

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;
	void Format();

	// ���탌�V�sGet�t���O
	bool canWoodSword_			= true;
	bool canJawaSword_			= true;
	bool canEnriSword_			= false;
	bool canKeinSword_			= false;
	bool canShizukuSword_		= false;
	bool canSaintSword_			= false;
	bool canGodWoodSword_		= false;

	bool canStoneSword_			= true;
	bool canIronOreSword_		= true;
	bool canJadeSword_			= false;
	bool canDiamondSword_		= false;
	bool canCarbonadeSword_		= false;
	bool canOrichalcumSword_	= false;
	bool canGodStoneSword_		= false;

	std::vector<bool> canWeaponMake_{ canWoodSword_		, canJawaSword_		 , canEnriSword_	, canKeinSword_,
									  canShizukuSword_	, canSaintSword_	 , canGodWoodSword_ ,
									  canStoneSword_	, canIronOreSword_	 , canJadeSword_	, canDiamondSword_,
									  canCarbonadeSword_, canOrichalcumSword_, canGodStoneSword_ };
private:

	void GetHandleForWeaponMake();
	void GetMainForWeaponMake(int ItemType);

	bool AlreadySecectItem(int ItemPosOnPouch);

	const int branchNum_ = 0;
	const int lumberNum_ = 1;
	const int pieceNum_  = 2;
	const int stoneNum_  = 3;

	const int woodsNum_  = 0;
	const int oresNum_   = 1;

	const int iconSize_  = 66;

	const int CursorX_Min_RecipeSelection_			  = 77;
	const int CursorY_Min_RecipeSelection_			  = 175;
	const int CursorX_Max_RecipeSelection_			  = 304;
	const int CursorY_Max_RecipeSelection_			  = 604;
	const int CursorY_MoveVerticalWidth_RecipeSelect_ = 33;
	const int WeaponID_ByLineBreak_RecipeSelection_	  = 2;

	const int CursorX_Min_ItemSelect_				  = 84;
	const int CursorY_Min_ItemSelect_				  = 139;
	const int CursorX_Max_ItemSelect_				  = 444;
	const int CursorY_Max_ItemSelect_				  = 577;
	const int CursorX_MoveVerticalWidth_ItemSelect_	  = 72;
	const int CursorY_MoveVerticalWidth_ItemSelect_	  = 73;
	const int ItemID_ByLineBreak_ItemSelect_		  = 6;

	const int WindowX_CellSize_						  = 6;
	const int WindowY_CellSize_						  = 7;
	const int WindowCellSize_X_						  = 72;
	const int WindowCellSize_Y_						  = 73;

	const int CursorX_ProceedNextPart_				  = 997;
	const int CursorY_ProceedNextPart_				  = 647;

	const int MainSelect_MaxSize_					  = 6;
	const int HandleSelect_MaxSize_					  = 3;

	const int WindowX_								  = 60;
	const int WindowY_								  = 80;
	const int RecipeWindowX_						  = 120;
	const int SelectItemWindowX_					  = 600;
	const int NextButtonX_							  = 1000;
	const int NextButtonY_							  = 650;
 
	const int AlreadySelect_HandleItem_X_			  = 755;
	const int AlreadySelect_HandleItem_X_Diameter_	  = 117;
	const int AlreadySelect_HandleItem_Y_			  = 101;
	const int AlreadySelect_MainItem_X_				  = 668;
	const int AlreadySelect_MainItem_X_Diameter_	  = 80;
	const int AlreadySelect_MainItem_Y_				  = 277;
	const int MakeWeaponX_							  = 874;
	const int MakeWeaponY_							  = 428;
	const int MakeWeaponQualityX_					  = 864;
	const int MakeWeaponQualityY_					  = 420;

	const int DrawWeaponName_LeftLine_X_			  = 90;
	const int DrawWeaponName_RightLine_X_			  = 317;
	const int DrawWeaponName_Y_						  = 183;

	const int CsvSkipCell_							  = 2;
	const int CsvTypeCheckFine_						  = 5;
	const int CsvTypeCheck_							  = 6;
	const int CsvNecessaryItem_						  = 4;

	const int DetailWindowX_						  = 600;
	const int DetailWindowY_						  = 80;
	const int ItemNameX_							  = 650;
	const int ItemNameY_							  = 100;
	const int ItemQualityX_							  = 900;
	const int ItemInfoX_							  = 650;
	const int ItemInfoY_							  = 200;

	const int DrawFlashTiming_						  = 20;
	const int Divisor_								  = 30;

	const int itemX_								  = 84; 
	const int itemY_								  = 141;

	const int DrawMaxPouchSize_						  = 42;

	int cursorX_				= 0;	// �J�[�\�����W
	int cursorY_				= 0;
	int prevCursorY_			= 0;
	int weaponID_				= 0;
	int ItemType_				= 0;	// �I���ł���A�C�e���̎��
	int selectIconNum_			= 0;
	int count_					= 0;

	bool recipeSelection_		 = false;	// ���V�s��I�яI��������ǂ����̔���(�I�������true)
	bool itemSelection_			 = false;	// �A�C�e����I�яI��������ǂ����̔���
	bool cursorInit_			 = true;	// �J�[�\���̏�����

	bool shouldWeaponMainCreate_ = false;	// ���C�������쐬�t���O
	bool shouldCreate_		     = false;	// �����t���O
	bool shouldRetry_		     = false;	// ���Ȃ����t���O
	bool HandleSlectOk_		     = false;   // �����蕔���I�������t���O
	bool MainSlectOk_		     = false;   // ���C�������I�������t���O
	bool itemDetail_			 = false;
	bool NotDuplicateItemPos_	 = false;   // �|�[�`���ɂ�����A�C�e���ʒu���X�g���̏d�����p
	bool MakeEnd_				 = false;
	bool animationEnd_			 = false;
	bool weaponMakeAssert_		 = false;

	std::vector<int> itemForWeaponMake_;		  // ���퐶���ɕK�v�ȃA�C�e�����ꎞ�I�ɕۊǂ���vector
	std::vector<int> itemQualityForWeaponMake_;	  // ���퐶���ɕK�v�ȃA�C�e���̕i�����ꎞ�I�ɕۊǂ���vector
	std::vector<int> ItemPosOnThePouch_;
	std::vector<int> SelectItemPosOnThePouch_;

	std::vector<std::string> weaponName_;

	const int defaultDrawCount_ = 300;
	const int defaultAngle_	    = 360;

	int distToCenter_ = defaultDrawCount_;
	int animationX_	  = 0;
	int animationY_	  = 0;
	int angle_		  = defaultAngle_;

	int drawCounter_  = defaultDrawCount_;

	std::vector<int> drawItemID_;

	int scrollCount_ = 0;

	std::vector<int> PouchDrawErea_;
	std::vector<int> NowDrawPosOnPouch_;
};

#endif