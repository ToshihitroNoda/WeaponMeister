#include "Production.h"
#include "Input.h"
#include "DataCsv.h"
#include "Adv.h"
#include "Music.h"
#include <DxLib.h>

#include "RecipeSelect.h"
#include "ItemSelect.h"
#include "HandleItemSelect.h"
#include "MainItemSelect.h"
#include "CreateRun.h"
#include "ProductionFlagManager.h"

RecipeSelect recipeSelect;
ItemSelect itemSelect;
HandleItemSelect handleItemSelect;
MainItemSelect mainItemSelect;
CreateRun createRun;
ProductionFlagManager productionFlag;

void Production::Init()
{
	gm.image.Load(tag);

	recipeSelect.Init();

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
	if (!recipeSelect.recipeSelection_ && is_Operation_Description_Been_)
	{
		recipeSelect.Update();
	}

	/*----- �g�p�f�ޑI�� -----*/
	else if (is_Operation_Description_Been_)
	{
		if (!productionFlag.shouldCreate)
			itemSelect.Update();
		// �f�ޑI����B���퐶�� 
		else
			createRun.Update();
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
	if (productionFlag.doAllFormat)
		Format();

	productionFlag.Update();
}

void Production::Format()
{
	productionFlag.scrollCount = 0;
	// �t���O��������
	productionFlag.cursorInit = true;
	productionFlag.shouldWeaponMainCreate = false;
	recipeSelect.recipeSelection_ = false;
	productionFlag.shouldCreate = false;
	productionFlag.itemDetail = false;
	createRun.MakeEnd = false;
	productionFlag.doAllFormat = false;
	itemSelect.playErrorSound = false;
	// ���X�g���N���A(������)
	gm.handles.clear();
	gm.handlesQuality.clear();
	gm.main.clear();
	gm.mainQuality.clear();
	productionFlag.itemForWeaponMake.clear();
	productionFlag.itemQualityForWeaponMake.clear();
	productionFlag.SelectItemPosOnThePouch.clear();
	productionFlag.ItemPosOnThePouch.clear();
	recipeSelect.weaponName_.clear();
	// CSV��j��
	gm.itemData.clear();
	gm.weaponData.clear();
	// �ŏ��ɖ߂�
	productionFlag.Final();
	recipeSelect.Init();
}

void Production::Draw()
{
	DrawGraph(0, 0, gm.image.productionBack, TRUE);

	// �쐬����I�����`��
	if (!recipeSelect.recipeSelection_ && !createRun.MakeEnd)
	{
		recipeSelect.Draw();
	}
	// �f�ޑI�����`��
	else if (!createRun.MakeEnd)
	{
		itemSelect.Draw();
	}
	// �f�ޑI���㕐�퐶���A�j���[�V����
	else
	{
		createRun.Draw();
	}

	if (productionFlag.weaponMakeAssert)
	{
		if (!itemSelect.playErrorSound)
		{
			PlaySoundMem(Music::error_SE, DX_PLAYTYPE_BACK);
			itemSelect.playErrorSound = true;
		}
		std::string drawMassege = "�f�ސ�������Ȃ����A�K�v�f�ނ��I������Ă��܂���B";
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, Screen::height / 2, drawMassege.c_str(), gm.colorWhite);
		drawMassege = "Z�L�[�Ŗ߂�";
		DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
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


