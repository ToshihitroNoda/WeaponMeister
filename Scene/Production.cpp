#include "Production.h"
#include "Input.h"
#include "DataCsv.h"
#include "Adv.h"
#include "Music.h"
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
	if (!recipeSelect_.recipeSelection_ && is_Operation_Description_Been_)
	{
		recipeSelect_.Update();
	}

	/*----- 使用素材選択 -----*/
	else if (is_Operation_Description_Been_)
	{
		if (!productionFlag_.shouldCreate)
			itemSelect_.Update();
		// 素材選択後。武器生成 
		else
			createRun_.Update();
	}
	if (!is_Operation_Description_Been_)
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
	if (productionFlag_.doAllFormat)
		Format();

	productionFlag_.Update();
}

void Production::Format()
{
	productionFlag_.scrollCount = 0;
	// フラグを初期化
	productionFlag_.cursorInit = true;
	productionFlag_.shouldWeaponMainCreate = false;
	recipeSelect_.recipeSelection_ = false;
	productionFlag_.shouldCreate = false;
	productionFlag_.itemDetail = false;
	createRun_.MakeEnd = false;
	productionFlag_.doAllFormat = false;
	itemSelect_.playErrorSound = false;
	// リストをクリア(初期化)
	gm.handles.clear();
	gm.handlesQuality.clear();
	gm.main.clear();
	gm.mainQuality.clear();
	productionFlag_.itemForWeaponMake.clear();
	productionFlag_.itemQualityForWeaponMake.clear();
	productionFlag_.SelectItemPosOnThePouch.clear();
	productionFlag_.ItemPosOnThePouch.clear();
	recipeSelect_.weaponName_.clear();
	// CSVを破棄
	gm.itemData.clear();
	gm.weaponData.clear();
	// 最初に戻る
	productionFlag_.Final();
	recipeSelect_.Init();
}

void Production::Draw()
{
	DrawGraph(0, 0, gm.image.productionBack, TRUE);

	// 作成武器選択時描画
	if (!recipeSelect_.recipeSelection_ && !createRun_.MakeEnd)
	{
		recipeSelect_.Draw();
	}
	// 素材選択時描画
	else if (!createRun_.MakeEnd)
	{
		itemSelect_.Draw();
	}
	// 素材選択後武器生成アニメーション
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
		std::string drawMassege = "素材数が足りないか、必要素材が選択されていません。";
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, Screen::height / 2, drawMassege.c_str(), gm.colorWhite);
		drawMassege = "Zキーで戻る";
		DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}

	if (!is_Operation_Description_Been_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		std::string drawNextDescription = "Zキーで次へ";
		int DrawWidthUnder = GetDrawStringWidth(drawNextDescription.c_str(), -1);
		DrawString((Screen::width - DrawWidthUnder) / 2, (Screen::height - (Screen::height / 4) + 30), drawNextDescription.c_str(), gm.colorWhite);
		std::string drawMassege = description_[operationDescriptionMassegeNum_];
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}
}


