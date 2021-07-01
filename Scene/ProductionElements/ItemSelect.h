#ifndef ITEMSELECT_H_
#define ITEMSELECT_H_

#include "ProductionSectionBase.h"
#include "HandleItemSelect.h"
#include "MainItemSelect.h"

class ItemSelect : public ProductionSectionBase
{
public:
	ItemSelect() = default;
	~ItemSelect() = default;

	void Update() override;
	void Draw() override;

	bool playErrorSound = false;

private:
	HandleItemSelect handleItemSelectSection_;
	MainItemSelect   mainItemSelectSection_;

	void MoveCursor();

	const int CursorX_Min_ItemSelect_ = 84;
	const int CursorY_Min_ItemSelect_ = 139;
	const int CursorX_Max_ItemSelect_ = 444;
	const int CursorY_Max_ItemSelect_ = 577;
	const int CursorX_MoveVerticalWidth_ItemSelect_ = 72;
	const int CursorY_MoveVerticalWidth_ItemSelect_ = 73;
	const int ItemID_ByLineBreak_ItemSelect_ = 6;
	const int CursorX_ProceedNextPart_ = 997;
	const int CursorY_ProceedNextPart_ = 637;
	const int WindowX_CellSize_ = 6;
	const int WindowY_CellSize_ = 7;
	const int WindowCellSize_X_ = 72;
	const int WindowCellSize_Y_ = 73;

	const int WindowX_ = 60;
	const int WindowY_ = 80;
	const int SelectItemWindowX_ = 600;
	const int RecipeWindowY_ = 120;

	const int ArrowX_ = 540;
	const int ArrowYHandle_ = 100;
	const int ArrowYMain_ = 280;

	const int NextButtonX_ = 1000;
	const int NextButtonY_ = 640;

	const int OptionMenuX_ = 420;
	const int OptionMenuY_ = 705;
	const int MakeWeaponQualityX_ = 864;
	const int MakeWeaponQualityY_ = 420;

	const int MakeWeaponX_ = 874;
	const int MakeWeaponY_ = 428;
	const int AlreadySelect_MainItem_X_ = 668;

	const int itemX_ = 84;
	const int itemY_ = 141;
	const int iconSize_ = 66;
};

#endif