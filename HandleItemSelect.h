#ifndef HANDLEITEMSELECT_H_
#define HANDLEITEMSELECT_H_

#include "ProductionSectionBase.h"

class HandleItemSelect : public ProductionSectionBase
{
public:

	HandleItemSelect()  = default;
	~HandleItemSelect() = default;

	void Update() override;
	void Draw() override;

private:
	const int CursorX_Min_ItemSelect_ = 84;
	const int CursorY_Min_ItemSelect_ = 139;
	const int CursorX_Max_ItemSelect_ = 444;

	const int AlreadySelect_HandleItem_X_ = 755;
	const int AlreadySelect_HandleItem_X_Diameter_ = 117;
	const int AlreadySelect_HandleItem_Y_ = 101;

	const int WindowX_CellSize_ = 6;

	const int HandleSelect_MaxSize_ = 3;
};

#endif