#ifndef RECIPESELECT_H_
#define RECIPESELECT_H_

#include "ProductionSectionBase.h"

class RecipeSelect : public ProductionSectionBase
{
public:
	RecipeSelect() = default;
	~RecipeSelect() = default;

	void Init();
	void Update() override;
	void Draw() override;

	bool recipeSelection_ = false; // レシピを選び終わったかどうかの判定(終わったらtrue)
	bool isDead = false;

	std::vector<std::string> weaponName_;

private:
	void MoveCursor();

	const int CursorX_Min_RecipeSelection_ = 77;
	const int CursorY_Min_RecipeSelection_ = 175;
	const int CursorX_Max_RecipeSelection_ = 304;
	const int CursorY_Max_RecipeSelection_ = 604;
	const int CursorY_MoveVerticalWidth_RecipeSelect_ = 33;
	const int WeaponID_ByLineBreak_RecipeSelection_ = 2;

	const int CursorX_ProceedNextPart_ = 997;
	const int CursorY_ProceedNextPart_ = 637;

	const int WindowX_ = 60;
	const int RecipeWindowY_ = 120;
	const int NextButtonX_ = 1000;
	const int NextButtonY_ = 640;

	const int DrawWeaponName_LeftLine_X_ = 90;
	const int DrawWeaponName_RightLine_X_ = 317;
	const int DrawWeaponName_Y_ = 183;

	const int CsvSkipCell_ = 2;
	const int CsvTypeCheck_ = 6;

	const int OptionMenuX_ = 420;
	const int OptionMenuY_ = 705;

	std::vector<int> drawItemID_;
};

#endif