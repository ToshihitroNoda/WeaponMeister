#include "Sale.h"
#include "Input.h"
#include "Adv.h"

int Sale::saleAmount = 0;

void Sale::Init()
{
	gm.image.Load(tag);

	gm.weaponData.Load("Resource/Datas/WeaponData.csv");

	cursorX_ = CursorX_Min_ItemSelect_;
	cursorY_ = CursorY_Min_ItemSelect_;

	for (int i = 0; i < gm.weapons.size(); i++)
	{
		weaponPosOnPouch_.push_back(i);
		if (PouchDrawErea_.size() < DrawMaxPouchSize_)
			PouchDrawErea_.push_back(gm.weapons[i]);
		if (NowDrawPosOnPouch_.size() < DrawMaxPouchSize_)
			NowDrawPosOnPouch_.push_back(i);
	}

	// ���i�̎擾�A�v�Z
	for (int i = 0; i < gm.weapons.size(); i++)
	{
		int basePrice = gm.weaponData[CsvWeaponBasePrice_][gm.weapons[i] + CsvSkipCell_];
		int price = basePrice * (1 + ((float)gm.weaponQuality[i] / 100));
		weaponPrice_.push_back(price);
	}

	prevMoney_ = gm.money;
}

void Sale::Final()
{
	gm.image.Final();
	sm.currentScene.reset();
}

void Sale::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_RIGHT))
	{
		if (cursorX_ < CursorX_Max_ItemSelect_)
		{
			cursorX_ += CursorX_MoveVerticalWidth_ItemSelect_;
			prevCursorY_ = cursorY_;
			selectIconNum_++; // �I������Ă�ӏ��̃A�C�e���̔ԍ����擾
		}
		else
		{
			cursorX_ = CursorX_ProceedNextPart_;
			cursorY_ = CursorY_ProceedNextPart_;
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_LEFT))
	{
		if (cursorX_ > CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
		{
			cursorX_ -= CursorX_MoveVerticalWidth_ItemSelect_;
			prevCursorY_ = cursorY_;
			selectIconNum_--;
		}
		else if (cursorX_ > CursorX_Max_ItemSelect_)
		{
			cursorX_ = CursorX_Max_ItemSelect_;
			cursorY_ = prevCursorY_;
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_DOWN))
	{
		if (cursorY_ != CursorY_Max_ItemSelect_ &&
			cursorX_ <= CursorX_Max_ItemSelect_)
		{
			cursorY_ += CursorY_MoveVerticalWidth_ItemSelect_;
			prevCursorY_ = cursorY_;
			selectIconNum_ += ItemID_ByLineBreak_ItemSelect_;
		}
		else
		{
			if (gm.weapons.size() > DrawMaxPouchSize_)
			{
				if (PouchDrawErea_.size() > WindowX_CellSize_)
				{
					prevCursorY_ = cursorY_;
					selectIconNum_ += ItemID_ByLineBreak_ItemSelect_;

					// ��s�X�N���[��
					scrollCount_++;
					// �`�悷��A�C�e����vector�̍ŏ��̈�s���폜���A���Ɉ�s����
					// �܂��擪�̈�s�̍폜
					PouchDrawErea_.erase(PouchDrawErea_.begin(), PouchDrawErea_.begin() + WindowX_CellSize_);
					NowDrawPosOnPouch_.erase(NowDrawPosOnPouch_.begin(), NowDrawPosOnPouch_.begin() + WindowX_CellSize_);
					// ���Ɉ�s�ǉ��B
					/// i�̏����l		: �\���ł���ő吔 + �ǉ������ - ��
					/// for���̉����� : �\���ł���ő吔 + �ǉ�����񐔂܂�
					for (int i = DrawMaxPouchSize_ + (scrollCount_ * WindowX_CellSize_) - WindowX_CellSize_;
						i < DrawMaxPouchSize_ + (scrollCount_ * WindowX_CellSize_);
						i++)
					{
						if (i < gm.weapons.size())
						{
							PouchDrawErea_.push_back(gm.weapons[i]);
							NowDrawPosOnPouch_.push_back(weaponPosOnPouch_[i]);
						}
					}
				}
			}
		}
	}
	if (Input::GetButtonDown(PAD_INPUT_UP))
	{
		if (cursorY_ != CursorY_Min_ItemSelect_ &&
			cursorX_ <= CursorX_Max_ItemSelect_)
		{
			cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
			prevCursorY_ = cursorY_;
			selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;
		}
		else
		{
			if (scrollCount_ > 0)
			{
				prevCursorY_ = cursorY_;
				selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;

				scrollCount_--;
				if (PouchDrawErea_.size() == DrawMaxPouchSize_)		// �`�悳��Ă�E�B���h�E�����܂��Ă�ꍇ
				{
					PouchDrawErea_.erase(PouchDrawErea_.end() - WindowX_CellSize_, PouchDrawErea_.end());
					NowDrawPosOnPouch_.erase(NowDrawPosOnPouch_.end() - WindowX_CellSize_, NowDrawPosOnPouch_.end());
					// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
					for (int i = WindowX_CellSize_; i > 0; i--)
					{
						PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.weapons[scrollCount_ * WindowX_CellSize_ + i - 1]);
						NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), weaponPosOnPouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
					}
				}
				else if (PouchDrawErea_.size() > DrawMaxPouchSize_ - WindowX_CellSize_ &&
					PouchDrawErea_.size() < DrawMaxPouchSize_)		// �`�悳��Ă�E�B���h�E�̍Ō�̈�s�ɋ󂫂�����ꍇ
				{
					PouchDrawErea_.erase(PouchDrawErea_.end() - (PouchDrawErea_.size() % WindowX_CellSize_), PouchDrawErea_.end());
					NowDrawPosOnPouch_.erase(NowDrawPosOnPouch_.end() - (NowDrawPosOnPouch_.size() % WindowX_CellSize_), NowDrawPosOnPouch_.end());
					// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
					for (int i = WindowX_CellSize_; i > 0; i--)
					{
						PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.weapons[scrollCount_ * WindowX_CellSize_ + i - 1]);
						NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), weaponPosOnPouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
					}
				}
				else												// �`�悳��Ă�E�B���h�E�̉����s�����󂢂Ă���ꍇ
				{
					// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
					for (int i = WindowX_CellSize_; i > 0; i--)
					{
						PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.weapons[scrollCount_ * WindowX_CellSize_ + i - 1]);
						NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), weaponPosOnPouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
					}
				}
			}
		}
	}

	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		if (cursorX_ <= CursorX_Max_ItemSelect_)
		{
			if (selectIconNum_ < gm.weapons.size())
			{
				saleWeapons_.push_back(gm.weapons[selectIconNum_]);
				selectWeaponPos_.push_back(selectIconNum_);
				gm.money += weaponPrice_[selectIconNum_];

				for (int i = 0; i < alreadySelectWeaponPos_.size(); i++)
				{
					if (alreadySelectWeaponPos_[i] == selectWeaponPos_.back()) // �d�����Ă�����
					{
						/*-----�I������-----*/
						for (int j = 0; j < saleWeapons_.size(); j++)
						{
							if (saleWeapons_.back() == saleWeapons_[j])
							{
								saleWeapons_.erase(saleWeapons_.begin() + j);
								selectWeaponPos_.erase(selectWeaponPos_.begin() + j);
								gm.money -= weaponPrice_[selectIconNum_];
								alreadySelectWeaponPos_.erase(alreadySelectWeaponPos_.begin() + j);
								break;
							}
						}
						/*------------------*/
						/*-----�d������-----*/
						saleWeapons_.erase(saleWeapons_.end() - 1);			   // �Ō�ɒǉ��������(���ǉ��������)���폜
						selectWeaponPos_.erase(selectWeaponPos_.end() - 1);	  
						gm.money -= weaponPrice_[selectIconNum_];
						/*------------------*/
						alradySelect_ = true;
						break;
					}  
				}
				if (!alradySelect_)
					alreadySelectWeaponPos_.push_back(selectIconNum_);
				alradySelect_ = false;
			}
		}
		else
		{
			saleAmount = gm.money - prevMoney_;
			sm.LoadScene("Report");
		}
	}
}

void Sale::Draw()
{
	DrawGraph(MoneyWindowX_, MoneyWindowY_, gm.image.moneyWindow, TRUE);
	DrawGraph(PouchWindowX_, PouchWindowY_, gm.image.itemWindow, TRUE);
	DrawGraph(DetailWindowX_, DetailWindowY_, gm.image.detailWindow, TRUE);
	DrawGraph(SaleButtonX_, SaleButtonY_, gm.image.sale, TRUE);
	
	SetFontSize(DrawMoneySize_);
	DrawString(DrawMoneyX_, DrawMoneyY_, std::to_string(gm.money).c_str(), gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);

	for (int y = 0; y < WindowY_CellSize_; y++)
	{
		for (int x = 0; x < WindowX_CellSize_; x++)
		{
			if ((signed)(x + (y * WindowX_CellSize_)) < PouchDrawErea_.size())
			{
				DrawGraph(itemX_ + x * WindowCellSize_X_, itemY_ + y * WindowCellSize_Y_, gm.image.weaponIcons[PouchDrawErea_[x + (y * WindowX_CellSize_)]], TRUE);
			}
		}
	}


	int shadowY = 0;
	int shadowX = 0;
	for (int i = 0; i < selectWeaponPos_.size(); i++)
	{
		for (int j = 0; j < NowDrawPosOnPouch_.size(); j++)
		{
			if (selectWeaponPos_[i] == NowDrawPosOnPouch_[j])
			{
				if (j < ItemID_ByLineBreak_ItemSelect_)
				{
					shadowX = j;
					shadowY = 0;
				}
				else
				{
					shadowX = j - ItemID_ByLineBreak_ItemSelect_ * (j / ItemID_ByLineBreak_ItemSelect_);
					shadowY = j / ItemID_ByLineBreak_ItemSelect_;
				}

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
				DrawBox
				(itemX_ + (shadowX * CursorX_MoveVerticalWidth_ItemSelect_),
					itemY_ + (shadowY * CursorY_MoveVerticalWidth_ItemSelect_),
					itemX_ + (shadowX * CursorX_MoveVerticalWidth_ItemSelect_ + iconSize_),
					itemY_ + (shadowY * CursorY_MoveVerticalWidth_ItemSelect_ + iconSize_),
					gm.colorGray,
					TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				DrawString
				(itemX_ + (shadowX * CursorX_MoveVerticalWidth_ItemSelect_),
					itemY_ + (shadowY * CursorY_MoveVerticalWidth_ItemSelect_),
					"�I��",
					gm.colorWhite);
			}
		}
	}

	if (selectIconNum_ < gm.weapons.size())
	{
		DrawString(ItemNameX_, ItemNameY_, gm.weaponData[0][gm.weapons[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
		std::stringstream quality;
		quality << gm.weaponQuality[selectIconNum_];
		DrawString(ItemQualityX_, ItemNameY_, ("�i�� : " + quality.str()).c_str(), gm.colorWhite);
		DrawString(ItemInfoX_, ItemInfoY_, gm.weaponData[1][gm.weapons[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
		std::stringstream price;
		price << weaponPrice_[selectIconNum_];
		DrawString(PriceX_, PriceY_, ("���i : " + price.str()).c_str(), gm.colorWhite);
	}

	if (cursorX_ >= CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
		DrawGraph(cursorX_, cursorY_, gm.image.itemSelection, TRUE);

	if (cursorX_ > CursorX_Max_ItemSelect_)
		DrawGraph(cursorX_, cursorY_, gm.image.nextCursor, TRUE);
}
