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

	int getItem_                        = 0;  // 手に入れたアイテムID
	int getItemCount_                   = 0;  // 一度に手に入れられるアイテム数
	int getItemCountMax_                = 5;  // 一度に手に入れられるアイテム数の最大値
	int qualityStorage_                 = 0;  // 品質一時保管変数
	int getItemDrawCounter_             = 0;
	int itemX_                          = 84; // アイテムアイコン座標
	int itemY_                          = 141;
	int cursorX_                        = CursorX_Min_ItemSelect_;	// カーソル座標
	int cursorY_                        = CursorY_Min_ItemSelect_;
	int selectIconNum_                  = 0;
	int scrollCount_                    = 0;
	int startCount_                     = 120;
	int endCount_                       = 120;
	int collectTimer_                   = 7200;	 // 採取時間。2分
	int backGroundHandle_               = 0;
	int operationDescriptionMessageNum_ = 0;

	float watchPointerAngle_ = 0.0f; // 時計の針の角度。1フレームで+=0.05fすると2分で一周
	float plusPointerAngle_  = 0.05f;

	bool getItemFlg_                    = false; // アイテムゲットフラグ
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
	{ "それでは早速採取を始めていきましょう！",
	  "キーボードのWASDで移動、マウスでカメラ操作が行えます。",
	  "画面右上の時計が一周したら採取終了となります。それまでに多くの素材を集めましょう。",
	  "マップ上の白く光っているオブジェクトに近づくと素材を採取できます。",
	  "Cキーを押すことで採取済みのアイテムを確認することができます。",
	  "以上が説明になります。それでは採取を始めてみましょう！"
	};
};

#endif

