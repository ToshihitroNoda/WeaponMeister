#include "Report.h"

#include <DxLib.h>
#include <string>
#include "Input.h"
#include "Adv.h"
#include "Buy.h"
#include "Sale.h"

int Report::prevMoney = 0;

void Report::Init()
{
	firstMoney_  = gm.money;
	Rent_		= (int)(RentBase_ * (Adv::day * RentMultiplied_));
	finalMoney_ = gm.money - Rent_;
}

void Report::Final()
{
	
}

void Report::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		if (pressCount_ < DrawDataNums_)
		{
			pressCount_++;
		}
		else
		{
			gm.money = finalMoney_;
			prevMoney = finalMoney_;
			if (Adv::day == LastDay_)
				sm.LoadScene("GameClear");
			else
				sm.LoadScene("Adv");
		}
	}
}

void Report::Draw()
{
	if (pressCount_ >= prevDraw_)
		DrawString(PrevMoneyX_, PrevMoneyY_, std::to_string(prevMoney).c_str(), gm.colorWhite);
	if (pressCount_ >= buyAmountDraw_)
		DrawString(BuyAmountX_, BuyAmountY_, std::to_string(Buy::buyAmount).c_str(), gm.colorRed);
	if (pressCount_ >= saleAmountDraw_)
		DrawString(SaleAmountX_, SaleAmountY_, std::to_string(Sale::saleAmount).c_str(), gm.colorBlue);
	if (pressCount_ >= haveMoneyDraw_)
		DrawString(HaveMoneyX_, HaveMoneyY_, std::to_string(firstMoney_).c_str(), gm.colorWhite);
	if (pressCount_ >= rentDraw_)
		DrawString(RentX_, RentY_, std::to_string(Rent_).c_str(), gm.colorRed);
	if (pressCount_ >= finalMoneyDraw_)
		DrawString(FinalMoneyX_, FinalMoneyY_, std::to_string(finalMoney_).c_str(), gm.colorWhite);

	if (pressCount_ >= DrawDataNums_)
		DrawString(NextMassegeX_, NextMassegeY_, "Zキーで終了", gm.colorWhite);
	else
		DrawString(NextMassegeX_, NextMassegeY_, "Zキーで次へ", gm.colorWhite);

}