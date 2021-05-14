#include "Report.h"

#include <DxLib.h>
#include <string>
#include <sstream>
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
			else if (finalMoney_ < 0)
				sm.LoadScene("GameOver");
			else
				sm.LoadScene("Adv");
		}
	}
}

void Report::Draw()
{
	SetFontSize(FontSize_);
	if (pressCount_ >= prevDraw_)
	{
		std::stringstream pM;
		pM << prevMoney;
		DrawString(PrevMoneyX_, PrevMoneyY_, ("前日の所持金　　　 : " + pM.str()).c_str(), gm.colorWhite);
	}
	if (pressCount_ >= buyAmountDraw_)
	{
		std::stringstream bA;
		bA << Buy::buyAmount;
		DrawString(BuyAmountX_, BuyAmountY_, ("買い物で使った金額 : " + bA.str()).c_str(), gm.colorRed);
	}
	if (pressCount_ >= saleAmountDraw_)
	{
		std::stringstream sA;
		sA << Sale::saleAmount;
		DrawString(SaleAmountX_, SaleAmountY_, ("売却で稼いだ金額　 : " + sA.str()).c_str(), gm.colorBlue);
	}
	if (pressCount_ >= haveMoneyDraw_)
	{
		std::stringstream fM;
		fM << firstMoney_;
		DrawString(HaveMoneyX_, HaveMoneyY_, ("現在の所持金　　　 : " + fM.str()).c_str(), gm.colorWhite);
	}
	if (pressCount_ >= rentDraw_)
	{
		std::stringstream r;
		r << Rent_;
		DrawString(RentX_, RentY_, ("本日の家賃　　　　 : " + r.str()).c_str(), gm.colorRed);
	}
	if (pressCount_ >= finalMoneyDraw_)
	{
		std::stringstream fM;
		fM << finalMoney_;
		DrawString(FinalMoneyX_, FinalMoneyY_, ("最終的な所持金　　 : " + fM.str()).c_str(), gm.colorWhite);

	}
	if (pressCount_ >= DrawDataNums_)
		DrawString(NextMassegeX_, NextMassegeY_, "Zキーで終了", gm.colorWhite);
	else
		DrawString(NextMassegeX_, NextMassegeY_, "Zキーで次へ", gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);

}