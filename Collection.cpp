#include "Collection.h"

#include "GameObject.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include "DataCsv.h"
#include "FieldItem.h"
#include "MyRandom.h"
#include "Input.h"

void Collection::Init()
{
	gm.mapData.Load("Resource/Datas/MapData.csv");
	gm.itemData.Load("Resource/Datas/ItemData.csv");

	SetUseZBuffer3D(TRUE);
	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	gm.map	  = std::make_shared<Map>(0, "Map1");
	gm.player = std::make_shared<Player>
				(gm.mapData[3][stageSelection.stageNum + CsvSkipCell_],
				 gm.mapData[4][stageSelection.stageNum + CsvSkipCell_],
				 gm.mapData[5][stageSelection.stageNum + CsvSkipCell_]);

	gm.player->Init();
	
	// �A�C�e���z��̍s�����擾
	int n1	  = gm.itemData[0].size();

	// �s����for���񂵂�ItemData�t�@�C����2,3��ڂ�map�ԍ��ƌ��݂���map�����������̂������o��
	for (int i = 0; i < n1; i++)
	{
		if ((int)gm.itemData[CsvCanGetMap1_][i] == stageSelection.stageNum ||
			(int)gm.itemData[CsvCanGetMap2_][i] == stageSelection.stageNum)
			possibilityToGetItem_.push_back(gm.itemData[CsvItemID_][i]); // �A�C�e��ID���l���ł���A�C�e�����X�g�Ɋi�[
	}
}

void Collection::Final()
{

}

void Collection::Update()
{
	if (!menuInit)
		gm.player->Update(); // �v���C���̍X�V

	// �t�B�[���h�A�C�e���̍X�V
	for (const auto& f : gm.fieldItems)
	{
		f->Update();
	}

	if (!menuInit)
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
				ItemGet();
			}
		}
	}
	if (getItemFlg_)
		getItemDrawCounter_++;

	if (getItemDrawCounter_ >= 120 || (getItemDrawCounter_ >= 5 && Input::GetButtonDown(PAD_INPUT_1)))
	{
		getItemFlg_		    = false; // ��ɓ��ꂽ�A�C�e���\��������
		getItemDrawCounter_ = 0;
		DrawGetItem_.clear();
	}

	gm.EraseRemoveIf(gm.fieldItems,
		[](std::shared_ptr<FieldItem>& ptr) { return ptr->isDead; });

	if (Input::GetButtonDown(PAD_INPUT_2))
	{
		if (menuOpen_ )
		{
			menuOpen_ = false;
			menuInit  = false;
			PouchDrawErea_.clear();
		}
		else
			sm.LoadScene("Buy");
	}

	if (!menuOpen_ && Input::GetButtonDown(PAD_INPUT_3))
	{
		menuOpen_	 = true;
		int cursorX_ = CursorX_Min_ItemSelect_;
		int cursorY_ = CursorY_Min_ItemSelect_;
	}

	if (menuOpen_)
	{
		if (!menuInit)
		{
			for (int i = 0; i < DrawMaxPouchSize; i++)
			{
				if (gm.pouch.size() > i)
					PouchDrawErea_.push_back(gm.pouch[i]);
			}
			menuInit = true;
		}
		/*----- �J�[�\���ړ� -----*/

		if (Input::GetButtonDown(PAD_INPUT_RIGHT))
		{
			if (cursorX_ < CursorX_Max_ItemSelect_)
			{
				cursorX_ += CursorX_MoveVerticalWidth_ItemSelect_;
				selectIconNum_++; // �I������Ă�ӏ��̃A�C�e���̔ԍ����擾
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_LEFT))
		{
			if (cursorX_ > CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
			{
				cursorX_ -= CursorX_MoveVerticalWidth_ItemSelect_;
				selectIconNum_--;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_DOWN))
		{
			if (cursorY_ != CursorY_Max_ItemSelect_)
			{
				cursorY_ += CursorY_MoveVerticalWidth_ItemSelect_;
				selectIconNum_ += WaponID_ByLineBreak_ItemSelect_;
			}
			else
			{
				if (gm.pouch.size() > DrawMaxPouchSize)
				{
					if (PouchDrawErea_.size() > WindowX_CellSize_)
					{
						// ��s�X�N���[��
						scrollCount++;
						// �`�悷��A�C�e����vector�̍ŏ��̈�s���폜���A���Ɉ�s����
						// �܂��擪�̈�s�̍폜
						PouchDrawErea_.erase(PouchDrawErea_.begin(), PouchDrawErea_.begin() + WindowX_CellSize_);
						// ���Ɉ�s�ǉ��B
						/// i�̏����l		: �\���ł���ő吔 + �ǉ������ - ��
						/// for���̉����� : �\���ł���ő吔 + �ǉ�����񐔂܂�
						for (int i = DrawMaxPouchSize + (scrollCount * WindowX_CellSize_) - WindowX_CellSize_;
							i < DrawMaxPouchSize + (scrollCount * WindowX_CellSize_);
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
		if (Input::GetButtonDown(PAD_INPUT_UP))
		{
			if (cursorY_ != CursorY_Min_ItemSelect_)
			{
				cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
				selectIconNum_ -= WaponID_ByLineBreak_ItemSelect_;
			}
			else
			{
				if (scrollCount > 0)
				{
					scrollCount--;
					if (PouchDrawErea_.size() == DrawMaxPouchSize)		// �`�悳��Ă�E�B���h�E�����܂��Ă�ꍇ
					{
						PouchDrawErea_.erase(PouchDrawErea_.end() - WindowX_CellSize_, PouchDrawErea_.end());
						// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
						for (int i = WindowX_CellSize_; i > 0; i--)
							PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount * WindowX_CellSize_ + i - 1]);
					}
					else if (PouchDrawErea_.size() > DrawMaxPouchSize - WindowX_CellSize_ &&
							 PouchDrawErea_.size() < DrawMaxPouchSize)	// �`�悳��Ă�E�B���h�E�̍Ō�̈�s�ɋ󂫂�����ꍇ
					{
						PouchDrawErea_.erase(PouchDrawErea_.end() - (PouchDrawErea_.size() % WindowX_CellSize_), PouchDrawErea_.end());
						// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
						for (int i = WindowX_CellSize_; i > 0; i--)
							PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount * WindowX_CellSize_ + i - 1]);
					} 
					else												// �`�悳��Ă�E�B���h�E�̉����s�����󂢂Ă���ꍇ
					{							
						// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
						for (int i = WindowX_CellSize_; i > 0; i--)
							PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount * WindowX_CellSize_ + i - 1]);
					}
				}
			}
		}

		/*---------------*/
	}
}

void Collection::ItemGet()
{
	// ������
	getItemCount_   = 0;
	getItem_		= 0;
	qualityStorage_ = 0;

	// �A�C�e���擾
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		if (gm.pouch.size() != MaxPouchSize_) // �o�b�O�������ς�����Ȃ�������
		{
			getItemFlg_ = true; // ��ɓ��ꂽ�A�C�e����\��
			// ������ɓ������A�C�e�����ő吔����ɓ��������o�b�O�̗e�ʂ��z������
			if ((signed)MaxPouchSize_ < gm.pouch.size() + getItemCountMax_)
			{
				getItemCountMax_--; // �ő�l�����炷
				return; // ������x�`�F�b�N
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

				qualityStorage_ = MyRandom::RangeInt(gm.mapData[1][stageSelection.stageNum + CsvSkipCell_], gm.mapData[2][stageSelection.stageNum + CsvSkipCell_]);
				int randItems = MyRandom::RangeInt(0, possibilityToGetItem_.size() - 1);
				getItem_ = possibilityToGetItem_[randItems];
				
				DrawGetItem_.push_back(getItem_); 
				gm.pouch.push_back(getItem_);
				gm.pouchQuality.push_back(qualityStorage_);
			}
		}
	}
}

void Collection::Draw()
{

	MV1SetPosition(Image::SkyBox, VGet(0, 0, 0));
	MV1SetScale(Image::SkyBox, VGet(10.0f, 10.0f, 10.0f));
	MV1DrawModel(Image::SkyBox);
	gm.map->DrawTerrain(); // �}�b�v�̕`��
	gm.map->DrawObjects(); // �I�u�W�F�N�g�̕`��

	gm.player->Draw(); // �v���C���[�̕`��

	// �t�B�[���h�A�C�e��
	for (const auto& f : gm.fieldItems)
	{
		f->Draw();
	}

	// �I�u�W�F�N�g
	for (const auto& mO : gm.mapObjects)
	{
		mO->Draw();
	}

	gm.player->DrawHitBox(); // �����蔻��̕`�� 

	if (getItemFlg_)
	{
		for (int i = 0; i < getItemCount_; i++)
		{
			DrawGraph(DrawGetItemX_ + i * DrawGetItemX_Width_, DrawGetItemY_, Image::itemIconWindow, TRUE);
			DrawGraph(DrawGetItemX_ + i * DrawGetItemX_Width_, DrawGetItemY_, Image::itemIcons[DrawGetItem_[i]], TRUE);
		}
	}


	for (int i = 0; i < gm.fieldItems.size(); i++)
	{
		if (gm.fieldItems[i]->isOnCollisionPlayer_)
			DrawString(Screen::Width / 2, Screen::Height / 2, "Z�L�[�ō̎�", gm.colorWhite);
	}
	if (gm.pouch.size() == MaxPouchSize_)
		DrawString
		(DrawAssertPouchSizeOverFlow_X_,
		 DrawAssertPouchSizeOverFlow_Y_,
		 "�|�[�`�������ς��ł�",
		 gm.colorWhite);

	if (menuOpen_)
	{
		DrawGraph(WindowX_, WindowY_, Image::itemWindow, TRUE);

		for (int y = 0; y < WindowY_CellSize_; y++)
		{
			for (int x = 0; x < WindowX_CellSize_; x++)
			{
				if ((signed)(x + (y * WindowX_CellSize_)) < PouchDrawErea_.size())
				{
					DrawGraph(itemX_ + x * WindowCellSize_X_, itemY_ + y * WindowCellSize_Y_, Image::itemIcons[PouchDrawErea_[x + (y * WindowX_CellSize_)]], TRUE);
				}
			}
		}

		if (cursorX_ >= CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
			DrawGraph(cursorX_, cursorY_, Image::itemSelection, TRUE);

		if (PouchDrawErea_.size() > (signed)selectIconNum_)
		{
			DrawGraph(DetailWindowX_, DetailWindowY_, Image::detailWindow, TRUE);
			DrawString(ItemNameX_, ItemNameY_, gm.itemData[0][PouchDrawErea_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
			std::stringstream ss;
			ss << gm.pouchQuality[selectIconNum_];
			DrawString(ItemQualityX_, ItemNameY_, ("�i�� : " + ss.str()).c_str(), gm.colorWhite);								
			DrawString(ItemInfoX_, ItemInfoY_, gm.itemData[1][PouchDrawErea_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
		}	

	}
}