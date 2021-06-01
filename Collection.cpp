#include "Collection.h"

#include "GameObject.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include "DataCsv.h"
#include "FieldItem.h"
#include "MyRandom.h"
#include "Input.h"
#include "Screen.h"
#include "Adv.h"
#include "Music.h"

void Collection::Init()
{
	gm.image.Load(tag);
	gm.mapData.Load("Resource/Datas/MapData.csv");
	gm.itemData.Load("Resource/Datas/ItemData.csv");

	SetUseZBuffer3D(TRUE);
	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	gm.map = std::make_shared<Map>(0, "Map" + std::to_string(StageSelection::stageNum));
	gm.player = std::make_shared<Player>
		(gm.mapData[3][StageSelection::stageNum - 1 + CsvSkipCell_],
			gm.mapData[4][StageSelection::stageNum - 1 + CsvSkipCell_],
			gm.mapData[5][StageSelection::stageNum - 1 + CsvSkipCell_]);

	gm.player->Init();

	gm.map->LoadTerrain(); // �}�b�v�̕`��
	gm.map->LoadObjects(); // �I�u�W�F�N�g�̕`��

	if (StageSelection::stageNum == 1 ||
		StageSelection::stageNum == 2 ||
		StageSelection::stageNum == 5)
	{
		SetLightDifColor(GetColorF(1.0f, 1.0f, 1.0f, 0.0f));
		backGroundHandle_ = gm.image.skyBack;
		if (StageSelection::stageNum == 1)
			PlaySoundMem(Music::stage1_BGM, DX_PLAYTYPE_LOOP);
		else if (StageSelection::stageNum == 2)
			PlaySoundMem(Music::stage2_BGM, DX_PLAYTYPE_LOOP);
		else
			PlaySoundMem(Music::stage5_BGM, DX_PLAYTYPE_LOOP);
	}
	else if (StageSelection::stageNum == 3)
	{
		SetLightDifColor(GetColorF(1.0f, 1.0f, 0.8f, 0.0f));
		backGroundHandle_ = gm.image.rockBack;
		PlaySoundMem(Music::stage3_BGM, DX_PLAYTYPE_LOOP);
	}
	else if (StageSelection::stageNum == 4)
	{
		SetLightDifColor(GetColorF(1.0f, 0.8f, 0.8f, 0.0f));
		backGroundHandle_ = gm.image.volcanoBack;
		PlaySoundMem(Music::stage4_BGM, DX_PLAYTYPE_LOOP);
	}

	if (Adv::day != 1)
		is_Operation_Description_Been_ = true;

	// �A�C�e���z��̍s�����擾
	int n1 = gm.itemData[0].size();

	// �s����for���񂵂�ItemData�t�@�C����2,3��ڂ�map�ԍ��ƌ��݂���map�����������̂������o��
	for (int i = 0; i < n1; i++)
	{
		if ((int)gm.itemData[CsvCanGetMap1_][i] == StageSelection::stageNum - 1 ||
			(int)gm.itemData[CsvCanGetMap2_][i] == StageSelection::stageNum - 1)
			possibilityToGetItem_.push_back(gm.itemData[CsvItemID_][i]); // �A�C�e��ID���l���ł���A�C�e�����X�g�Ɋi�[
	}
}

void Collection::Final()
{
	StopSoundMem(Music::stage1_BGM);
	StopSoundMem(Music::stage2_BGM);
	StopSoundMem(Music::stage3_BGM);
	StopSoundMem(Music::stage4_BGM);
	StopSoundMem(Music::stage5_BGM);

	gm.mapObjects.clear();
	gm.fieldItems.clear();
	gm.mapTerrain.clear();
	gm.map.reset();
	gm.player.reset();
	gm.image.Final();
	sm.currentScene.reset();
}

void Collection::Update()
{
	if (!playStartSound_ && is_Operation_Description_Been_)
	{
		PlaySoundMem(Music::collectionstart_SE, DX_PLAYTYPE_BACK);
		playStartSound_ = true;
	}
	if (collectTimer_ > 0 && startCount_ < 0 && is_Operation_Description_Been_)
	{
		if (!menuOpen_)
			gm.player->Update(); // �v���C���̍X�V

		// �t�B�[���h�A�C�e���̍X�V
		for (const auto& fI : gm.fieldItems)
		{
			fI->Update();
		}

		if (!menuOpen_)
		{
			// �v���C���[�ƃt�B�[���h�A�C�e���Ƃ̓����蔻��
			for (int i = 0; i < (signed)gm.fieldItems.size(); i++)
			{
				if (MyMath::RectRectIntersect(
					gm.player->GetLeft(), gm.player->GetBack(), gm.player->GetRight(), gm.player->GetForward(),
					gm.fieldItems[i]->GetLeft(), gm.fieldItems[i]->GetBack(), gm.fieldItems[i]->GetRight(), gm.fieldItems[i]->GetForward()
				))
				{
					gm.player->OnCollision(gm.fieldItems[i]);
					gm.fieldItems[i]->OnCollision(gm.player);
					if (gm.pouch.size() != gm.MaxPouchSize)
					{
						ItemGet();
					}
				}
			}
			// �v���C���[�ƃ}�b�v�I�u�W�F�N�g�̓����蔻��
			for (int i = 0; i < (signed)gm.mapObjects.size(); i++)
			{
				if (MyMath::RectRectIntersect(
					gm.player->GetLeft(), gm.player->GetBack(), gm.player->GetRight(), gm.player->GetForward(),
					gm.mapObjects[i]->GetLeft(), gm.mapObjects[i]->GetBack(), gm.mapObjects[i]->GetRight(), gm.mapObjects[i]->GetForward()
				))
				{
					gm.player->OnCollision(gm.mapObjects[i]);
					gm.mapObjects[i]->OnCollision(gm.player);
				}
			}
		}
		if (getItemFlg_)
			getItemDrawCounter_++;

		if (getItemDrawCounter_ >= 120 || (getItemDrawCounter_ >= 5 && Input::GetButtonDown(PAD_INPUT_1)))
		{
			getItemFlg_ = false; // ��ɓ��ꂽ�A�C�e���\��������
			getItemDrawCounter_ = 0;
			DrawGetItem_.clear();
		}

		gm.EraseRemoveIf(gm.fieldItems,
			[](std::shared_ptr<FieldItem>& ptr) { return ptr->isDead; });

		if (Input::GetButtonDown(PAD_INPUT_2))
		{
			if (menuOpen_)
			{
				PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
				menuOpen_ = false;
				menuInit_ = false;
				PouchDrawErea_.clear();
			}
		}

		if (!menuOpen_ && Input::GetButtonDown(PAD_INPUT_3))
		{
			PlaySoundMem(Music::menuopen_SE, DX_PLAYTYPE_BACK);
			menuOpen_ = true;
			cursorX_ = CursorX_Min_ItemSelect_;
			cursorY_ = CursorY_Min_ItemSelect_;
		}

		if (menuOpen_)
		{
			if (!menuInit_)
			{
				for (int i = 0; i < DrawMaxPouchSize_; i++)
				{
					selectIconNum_ = 0;
					scrollCount_ = 0;
					if (gm.pouch.size() > i)
						PouchDrawErea_.push_back(gm.pouch[i]);
				}
				menuInit_ = true;
			}
			/*----- �J�[�\���ړ� -----*/

			if (Input::GetButtonDown(PAD_INPUT_RIGHT))
			{
				if (cursorX_ < CursorX_Max_ItemSelect_)
				{
					PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
					cursorX_ += CursorX_MoveVerticalWidth_ItemSelect_;
					selectIconNum_++; // �I������Ă�ӏ��̃A�C�e���̔ԍ����擾
				}
			}
			else if (Input::GetButtonDown(PAD_INPUT_LEFT))
			{
				if (cursorX_ > CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
				{
					PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
					cursorX_ -= CursorX_MoveVerticalWidth_ItemSelect_;
					selectIconNum_--;
				}
			}
			else if (Input::GetButtonDown(PAD_INPUT_DOWN))
			{
				if (cursorY_ != CursorY_Max_ItemSelect_)
				{
					PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
					cursorY_ += CursorY_MoveVerticalWidth_ItemSelect_;
					selectIconNum_ += WaponID_ByLineBreak_ItemSelect_;
				}
				else
				{
					if (gm.pouch.size() > DrawMaxPouchSize_)
					{
						if (PouchDrawErea_.size() > WindowX_CellSize_)
						{
							PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
							// ��s�X�N���[��
							scrollCount_++;
							// �`�悷��A�C�e����vector�̍ŏ��̈�s���폜���A���Ɉ�s����
							// �܂��擪�̈�s�̍폜
							PouchDrawErea_.erase(PouchDrawErea_.begin(), PouchDrawErea_.begin() + WindowX_CellSize_);
							// ���Ɉ�s�ǉ��B
							/// i�̏����l		: �\���ł���ő吔 + �ǉ������ - ��
							/// for���̉����� : �\���ł���ő吔 + �ǉ�����񐔂܂�
							for (int i = DrawMaxPouchSize_ + (scrollCount_ * WindowX_CellSize_) - WindowX_CellSize_;
								i < DrawMaxPouchSize_ + (scrollCount_ * WindowX_CellSize_);
								i++)
							{
								if (i < gm.pouch.size())
								{
									PouchDrawErea_.push_back(gm.pouch[i]);
								}
							}
						}
					}
				}
			}
			else if (Input::GetButtonDown(PAD_INPUT_UP))
			{
				if (cursorY_ != CursorY_Min_ItemSelect_)
				{
					PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
					cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
					selectIconNum_ -= WaponID_ByLineBreak_ItemSelect_;
				}
				else
				{
					if (scrollCount_ > 0)
					{
						PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
						scrollCount_--;
						if (PouchDrawErea_.size() == DrawMaxPouchSize_)		// �`�悳��Ă�E�B���h�E�����܂��Ă�ꍇ
						{
							PouchDrawErea_.erase(PouchDrawErea_.end() - WindowX_CellSize_, PouchDrawErea_.end());
							// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
							for (int i = WindowX_CellSize_; i > 0; i--)
								PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount_ * WindowX_CellSize_ + i - 1]);
						}
						else if (PouchDrawErea_.size() > DrawMaxPouchSize_ - WindowX_CellSize_ &&
							PouchDrawErea_.size() < DrawMaxPouchSize_)	// �`�悳��Ă�E�B���h�E�̍Ō�̈�s�ɋ󂫂�����ꍇ
						{
							PouchDrawErea_.erase(PouchDrawErea_.end() - (PouchDrawErea_.size() % WindowX_CellSize_), PouchDrawErea_.end());
							// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
							for (int i = WindowX_CellSize_; i > 0; i--)
								PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount_ * WindowX_CellSize_ + i - 1]);
						}
						else												// �`�悳��Ă�E�B���h�E�̉����s�����󂢂Ă���ꍇ
						{
							// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
							for (int i = WindowX_CellSize_; i > 0; i--)
								PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount_ * WindowX_CellSize_ + i - 1]);
						}
					}
				}
			}

			/*---------------*/
		}
		if (!menuOpen_)
		{
			collectTimer_--;
			watchPointerAngle_ += plusPointerAngle_;
		}
	}
	else if (collectTimer_ <= 0 && startCount_ < 0 && is_Operation_Description_Been_)
	{
		if (!playEndSound_)
		{
			PlaySoundMem(Music::collectionstart_SE, DX_PLAYTYPE_BACK);
			playEndSound_ = true;
		}
		collectionEnd_ = true;
		if (endCount_ < 0)
		{
			if (Input::GetButtonDown(PAD_INPUT_1))
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				clsDx();
				sm.LoadScene("Buy");
			}
		}
		endCount_--;
	}
	if (is_Operation_Description_Been_)
		startCount_--;
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
}

void Collection::ItemGet()
{
	// ������
	getItemCount_ = 0;
	getItem_ = 0;
	qualityStorage_ = 0;

	// �A�C�e���擾
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		PlaySoundMem(Music::collect_SE, DX_PLAYTYPE_BACK);
		getItemFlg_ = true; // ��ɓ��ꂽ�A�C�e����\��
		// ������ɓ������A�C�e�����ő吔����ɓ��������o�b�O�̗e�ʂ��z������
		if (gm.MaxPouchSize < gm.pouch.size() + getItemCountMax_)
		{
			while(gm.MaxPouchSize < gm.pouch.size() + getItemCountMax_)
				getItemCountMax_--; // �ő�l�����炷
		}

		// ��ɓ������A�C�e�����������_���Ō���
		getItemCount_ = MyRandom::RangeInt(1, getItemCountMax_);

		for (int i = 0; i < getItemCount_; i++)
		{
			// �}�b�v�ɉ����������_���i����ۊ�
			// ��ɓ������A�C�e���������_���Ŏ擾
			// ���ۂɃA�C�e������ɓ����

			// Draw�p�Ɏ�ɓ��ꂽ�A�C�e����vector�Ɋi�[
			// pouch��push_buck
			// �i���pvector�ɕi������

			qualityStorage_ = MyRandom::RangeInt(gm.mapData[1][StageSelection::stageNum - 1 + CsvSkipCell_], gm.mapData[2][StageSelection::stageNum - 1 + CsvSkipCell_]);
			int randItems = MyRandom::RangeInt(0, possibilityToGetItem_.size() - 1);
			getItem_ = possibilityToGetItem_[randItems];

			DrawGetItem_.push_back(getItem_);
			gm.pouch.push_back(getItem_);
			gm.pouchQuality.push_back(qualityStorage_);
		}
	}
}

void Collection::Draw()
{
	DrawGraph(gm.player->backX, 0, backGroundHandle_, TRUE);
	DrawGraph(gm.player->backX - gm.player->BackImageWidth, 0, backGroundHandle_, TRUE);

	// �n�`
	for (auto& mT : gm.mapTerrain)
	{
		mT->Draw();
	}

	gm.player->Draw(); // �v���C���[�̕`��

	// �t�B�[���h�A�C�e��
	for (const auto& fI : gm.fieldItems)
	{
		fI->Draw();
	}

	// �I�u�W�F�N�g
	for (const auto& mO : gm.mapObjects)
	{
		mO->Draw();
	}

	DrawRotaGraph(WatchX_, WatchY_, 1.0f, 0.0f, gm.image.watchBase, TRUE);
	DrawRotaGraph(WatchX_, WatchY_, 1.0f, watchPointerAngle_ * MyMath::Deg2Rad, gm.image.watchPointer, TRUE);

	if (getItemFlg_)
	{
		for (int i = 0; i < getItemCount_; i++)
		{
			DrawGraph(DrawGetItemX_ + i * DrawGetItemX_Width_, DrawGetItemY_, gm.image.itemIconWindow, TRUE);
			DrawGraph(DrawGetItemX_ + i * DrawGetItemX_Width_, DrawGetItemY_, gm.image.itemIcons[DrawGetItem_[i]], TRUE);
		}
	}


	for (int i = 0; i < gm.fieldItems.size(); i++)
	{
		if (gm.fieldItems[i]->isOnCollisionPlayer && gm.pouch.size() < gm.MaxPouchSize)
			DrawString(Screen::width / 2, Screen::height / 2, "Z�L�[�ō̎�", gm.colorWhite);

		if (gm.fieldItems[i]->isOnCollisionPlayer && gm.pouch.size() >= gm.MaxPouchSize)
		{
			DrawString(Screen::width / 2, Screen::height / 2, "�|�[�`�������ς��ł�", gm.colorWhite);
		}
	}

	if (menuOpen_)
	{
		DrawGraph(WindowX_, WindowY_, gm.image.itemWindow, TRUE);

		for (int y = 0; y < WindowY_CellSize_; y++)
		{
			for (int x = 0; x < WindowX_CellSize_; x++)
			{
				if ((signed)(x + (y * WindowX_CellSize_)) < PouchDrawErea_.size())
				{
					DrawGraph(itemX_ + x * WindowCellSize_X_, itemY_ + y * WindowCellSize_Y_, gm.image.itemIcons[PouchDrawErea_[x + (y * WindowX_CellSize_)]], TRUE);
				}
			}
		}

		if (cursorX_ >= CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
			DrawGraph(cursorX_, cursorY_, gm.image.itemSelection, TRUE);

		DrawString(DrawPouchSizeX_, DrawPouchSizeY_, (std::to_string(gm.pouch.size()) + " / 200").c_str(), gm.colorWhite);

		if (PouchDrawErea_.size() > selectIconNum_)
		{
			DrawGraph(DetailWindowX_, DetailWindowY_, gm.image.detailWindow, TRUE);
			DrawString(ItemNameX_, ItemNameY_, gm.itemData[0][PouchDrawErea_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
			std::stringstream ss;
			ss << gm.pouchQuality[selectIconNum_ + scrollCount_ * WindowX_CellSize_];
			DrawString(ItemQualityX_, ItemNameY_, ("�i�� : " + ss.str()).c_str(), gm.colorWhite);
			DrawString(ItemInfoX_, ItemInfoY_, gm.itemData[1][PouchDrawErea_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
		}
		SetFontSize(15);
		DrawString(OptionMenuPouchX_, OptionMenuPouchY_, "�������� : �J�[�\���ړ��@,�@X�L�[ : ����", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}
	else
	{
		SetFontSize(15);
		DrawString(OptionMenuX_, OptionMenuY_, "WASD : �ړ��@,�@�}�E�X : �J����  ,  C�L�[ : �|�[�`���J��", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}

	if (startCount_ >= 0)
		DrawGraph(0, 0, gm.image.collectionStart, TRUE);

	if (collectionEnd_)
	{
		DrawGraph(0, 0, gm.image.collectionEnd, TRUE);
		std::string drawNextDescription = "Z�L�[�Ŏ���";
		int DrawWidthUnder = GetDrawStringWidth(drawNextDescription.c_str(), -1);
		DrawString((Screen::width - DrawWidthUnder) / 2, (Screen::height - (Screen::height / 4) + 30), drawNextDescription.c_str(), gm.colorWhite);

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