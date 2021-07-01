#ifndef MAINITEMSELECT_H_
#define MAINITEMSELECT_H_

#include "../../GameManager.h"
#include "../SceneManager.h"
#include "ProductionSectionBase.h"

class MainItemSelect : public ProductionSectionBase
{
public: 
	GameManager& gm = GameManager::GetInstance();
	SceneManager& sm = SceneManager::GetInstance();

	MainItemSelect() = default;
	~MainItemSelect() = default;

	void Update() override;
	void Draw() override;

private:
	void addItem();
	void eraseItem();
	void allSelectEnd();

	const int WindowX_CellSize_ = 6;
	const int CursorX_Max_ItemSelect_ = 444;

	const int AlreadySelect_MainItem_X_ = 668;
	const int AlreadySelect_MainItem_X_Diameter_ = 80;
	const int AlreadySelect_MainItem_Y_ = 277;

	const int MainSelect_MaxSize_ = 6;

	const int CsvSkipCell_ = 2;
	const int CsvNecessaryItem_ = 4;
};

#endif