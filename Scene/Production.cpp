#include "Production.h"
#include "../MyLib/Input.h"
#include "../MyLib/DataCsv.h"
#include "Adv.h"
#include "../Music.h"
#include <DxLib.h>

void Production::Init()
{
	gm.image.Load(tag);

	recipeSelect_.Init();

	if (Adv::day != 1)
		is_Operation_Description_Been_ = true;
}

void Production::Final()
{
	StopSoundMem(Music::production_BGM);
	gm.image.Final();
	sm.currentScene.reset();
}

void Production::Update()
{
	if (recipeSelect_.isDead)
		isDead = true;

	if (!recipeSelect_.recipeSelection_ && is_Operation_Description_Been_)
		recipeSelect_.Update();
	// gpfÞIð
	else if (is_Operation_Description_Been_)
	{
		if (!productionFlag_.shouldCreate && recipeSelect_.recipeSelection_)
			itemSelect_.Update();
		// fÞIðãBí¶¬ 
		else if (productionFlag_.shouldCreate)
			createRun_.Update();
	}
	if (!is_Operation_Description_Been_)
	{
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
			if (operationDescriptionMessageNum_ < sizeof(description_) / sizeof(*description_) - 1)
				operationDescriptionMessageNum_++;
			else
				is_Operation_Description_Been_ = true;
		}
	}
	if (productionFlag_.doAllFormat)
		Format();

	productionFlag_.Update();
}

void Production::Format()
{
	productionFlag_.scrollCount = 0;
	// tOðú»
	productionFlag_.cursorInit = true;
	productionFlag_.shouldWeaponMainCreate = false;
	recipeSelect_.recipeSelection_ = false;
	productionFlag_.shouldCreate = false;
	productionFlag_.itemDetail = false;
	createRun_.MakeEnd = false;
	productionFlag_.doAllFormat = false;
	itemSelect_.playErrorSound = false;
	// XgðNA(ú»)
	gm.handles.clear();
	gm.main.clear();
	productionFlag_.itemForWeaponMake.clear();
	productionFlag_.itemQualityForWeaponMake.clear();
	productionFlag_.SelectItemPosOnThePouch.clear();
	productionFlag_.ItemPosOnThePouch.clear();
	recipeSelect_.weaponName_.clear();
	// CSVðjü
	gm.itemData.clear();
	gm.weaponData.clear();
	// ÅÉßé
	productionFlag_.Final();
	recipeSelect_.Init();
}

void Production::Change()
{
	sm.LoadScene("Sale");
}

void Production::Draw()
{
	DrawGraph(0, 0, gm.image.productionBack, TRUE);

	// ì¬íIð`æ
	if (!recipeSelect_.recipeSelection_ && !createRun_.MakeEnd)
	{
		recipeSelect_.Draw();
	}
	// fÞIð`æ
	else if (!createRun_.MakeEnd)
	{
		itemSelect_.Draw();
	}
	// fÞIðãí¶¬Aj[V
	else
	{
		createRun_.Draw();
	}

	if (productionFlag_.weaponMakeAssert)
	{
		if (!itemSelect_.playErrorSound)
		{
			PlaySoundMem(Music::error_SE, DX_PLAYTYPE_BACK);
			itemSelect_.playErrorSound = true;
		}
		std::string drawMassege = "fÞª«èÈ¢©AKvfÞªIð³êÄ¢Ü¹ñB";
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, Screen::height / 2, drawMassege.c_str(), gm.colorWhite);
		drawMassege = "ZL[Åßé";
		DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}

	if (!is_Operation_Description_Been_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		std::string drawNextDescription = "ZL[ÅÖ";
		int DrawWidthUnder = GetDrawStringWidth(drawNextDescription.c_str(), -1);
		DrawString((Screen::width - DrawWidthUnder) / 2, (Screen::height - (Screen::height / 4) + 30), drawNextDescription.c_str(), gm.colorWhite);
		std::string drawMassege = description_[operationDescriptionMessageNum_];
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}
}