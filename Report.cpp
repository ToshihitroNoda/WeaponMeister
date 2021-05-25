#include "Report.h"

#include <DxLib.h>
#include <string>
#include <sstream>
#include "Input.h"
#include "Adv.h"
#include "Buy.h"
#include "Sale.h"
#include "Music.h"
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

	if (gm.money < 0)		// ���������Ȃ�������Z�[�u���Ȃ��ŃQ�[���I�[�o�[
		dataSave.Save();

	if (Adv::day != 1)
		is_Operation_Description_Been_ = true;

	PlaySoundMem(Music::report_BGM, DX_PLAYTYPE_LOOP);
}

void Report::Final()
{
	StopSoundMem(Music::report_BGM);
	gm.image.Final();
	sm.currentScene.reset();
}

void Report::Update()
{
	if (is_Operation_Description_Been_)
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			if (pressCount_ < DrawDataNums_)
			{
				PlaySoundMem(Music::reportenter_SE, DX_PLAYTYPE_BACK);
				pressCount_++;
			}
			else
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				prevMoney = finalMoney_;

				if (finalMoney_ < 0)
					sm.LoadScene("GameOver");
				else
					sm.LoadScene("Adv");
			}
		}

		if (autoSaveCount_ >= 0)
			autoSaveCount_--;
	}
	else
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			if (operationDescriptionMassegeNum_ < sizeof(description_) / sizeof(*description_) - 1)
				operationDescriptionMassegeNum_++;
			else
				is_Operation_Description_Been_ = true;
		}
	}
}

void Report::Draw()
{
	DrawGraph(0, 0, gm.image.reportBack, TRUE);

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

	if (gm.money >= 0 && autoSaveCount_ > 0)
	{
		DrawString(AutoSaveX_, AutoSaveY_, "�Z�[�u��...", gm.colorWhite);
	}

	if (!is_Operation_Description_Been_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		std::string drawNextDescription = "Z�L�[�Ŏ���";
		int DrawWidthUnder = GetDrawStringWidth(drawNextDescription.c_str(), -1);
		DrawString((Screen::width - DrawWidthUnder) / 2, (Screen::height - (Screen::height / 4) + 30), drawNextDescription.c_str(), gm.colorWhite);
		std::string drawMassege = description_[operationDescriptionMassegeNum_];
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}
}