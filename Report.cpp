#include "Report.h"

#include <DxLib.h>
#include "Input.h"
#include "Adv.h"

void Report::Init()
{

}

void Report::Final()
{
	
}

void Report::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		if (Adv::day == LastDay_)
			sm.LoadScene("GameClear");
		else
			sm.LoadScene("Adv");
	}
}

void Report::Draw()
{
	DrawString(NextMassegeX_, NextMassegeY_, "ZÉLÅ[Ç≈èIóπ", gm.colorWhite);
}