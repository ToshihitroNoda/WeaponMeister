#include "Report.h"

#include <DxLib.h>
#include <string>
#include <sstream>
#include "Input.h"
#include "Adv.h"
#include "Buy.h"
#include "Sale.h"

#include "DataSave.h"

DataSave dataSave;

int Report::prevMoney = 0;

void Report::Init()
{
	gm.image.Load(tag);

	firstMoney_  = gm.money;
	Rent_		 = (int)(RentBase_ * (Adv::day * RentMultiplied_));
	nextRent_	 = (int)(RentBase_ * ((Adv::day + 1) * RentMultiplied_));
	finalMoney_  = gm.money - Rent_;

	gm.money = finalMoney_;

	dataSave.Save();
}

void Report::Final()
{
	gm.image.Final();
	sm.currentScene.reset();
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
		DrawString(PrevMoneyX_, PrevMoneyY_, ("�O���̏������@�@�@ : " + pM.str()).c_str(), gm.colorWhite);
	}
	if (pressCount_ >= buyAmountDraw_)
	{
		std::stringstream bA;
		bA << Buy::buyAmount;
		DrawString(BuyAmountX_, BuyAmountY_, ("�������Ŏg�������z : " + bA.str()).c_str(), gm.colorRed);
	}
	if (pressCount_ >= saleAmountDraw_)
	{
		std::stringstream sA;
		sA << Sale::saleAmount;
		DrawString(SaleAmountX_, SaleAmountY_, ("���p�ŉ҂������z�@ : " + sA.str()).c_str(), gm.colorBlue);
	}
	if (pressCount_ >= haveMoneyDraw_)
	{
		std::stringstream fM;
		fM << firstMoney_;
		DrawString(HaveMoneyX_, HaveMoneyY_, ("���݂̏������@�@�@ : " + fM.str()).c_str(), gm.colorWhite);
	}
	if (pressCount_ >= rentDraw_)
	{
		std::stringstream r;
		r << Rent_;
		DrawString(RentX_, RentY_, ("�{���̉ƒ��@�@�@�@ : " + r.str()).c_str(), gm.colorRed);
	}
	if (pressCount_ >= finalMoneyDraw_)
	{
		std::stringstream fM;
		fM << finalMoney_;
		DrawString(FinalMoneyX_, FinalMoneyY_, ("�ŏI�I�ȏ������@�@ : " + fM.str()).c_str(), gm.colorWhite);

	}
	if (pressCount_ >= nextRentDraw_)
	{
		std::stringstream nR;
		nR << nextRent_;
		DrawString(NextRentX_, NextRentY_, ("�����̉ƒ��@�@�@�@ : " + nR.str()).c_str(), gm.colorWhite);

	}
	if (pressCount_ >= DrawDataNums_)
		DrawString(NextMassegeX_, NextMassegeY_, "Z�L�[�ŏI��", gm.colorWhite);
	else
		DrawString(NextMassegeX_, NextMassegeY_, "Z�L�[�Ŏ���", gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);

}