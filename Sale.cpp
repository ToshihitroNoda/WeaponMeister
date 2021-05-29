#include "DataLoad.h"
#include "Sale.h"
#include "Input.h"
#include "Music.h"
#include "Adv.h"
#include <algorithm>

DataLoad dataload;

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
		if (pouchDrawErea_.size() < DrawMaxPouchSize_)
			pouchDrawErea_.push_back(gm.weapons[i]);
		if (nowDrawPosOnPouch_.size() < DrawMaxPouchSize_)
			nowDrawPosOnPouch_.push_back(i);
	}

	// ���i�̎擾�A�v�Z
	for (int i = 0; i < gm.weapons.size(); i++)
	{
		int basePrice = gm.weaponData[CsvWeaponBasePrice_][gm.weapons[i] + CsvSkipCell_];
		int price = basePrice * (1 + ((float)gm.weaponQuality[i] / 100));
		weaponPrice_.push_back(price);
	}

	prevMoney_ = gm.money;

	if (Adv::day != 1)
		is_Operation_Description_Been_ = true;

	PlaySoundMem(Music::sale_BGM, DX_PLAYTYPE_LOOP);
}

void Sale::Final()
{
	StopSoundMem(Music::sale_BGM);
	gm.image.Final();
	sm.currentScene.reset();
}

void Sale::Update()
{
	if (is_Operation_Description_Been_)
	{
		if (Input::GetButtonDown(PAD_INPUT_RIGHT))
		{
			if (cursorX_ < CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
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
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ -= CursorX_MoveVerticalWidth_ItemSelect_;
				prevCursorY_ = cursorY_;
				selectIconNum_--;
			}
			else if (cursorX_ > CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ = CursorX_Max_ItemSelect_;
				cursorY_ = prevCursorY_;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_DOWN))
		{
			if (cursorY_ != CursorY_Max_ItemSelect_ &&
				cursorX_ <= CursorX_Max_ItemSelect_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorY_ += CursorY_MoveVerticalWidth_ItemSelect_;
				prevCursorY_ = cursorY_;
				selectIconNum_ += ItemID_ByLineBreak_ItemSelect_;
			}
			else
			{
				if (gm.weapons.size() > DrawMaxPouchSize_)
				{
					if (pouchDrawErea_.size() > WindowX_CellSize_)
					{
						PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
						prevCursorY_ = cursorY_;
						selectIconNum_ += ItemID_ByLineBreak_ItemSelect_;

						// ��s�X�N���[��
						scrollCount_++;
						// �`�悷��A�C�e����vector�̍ŏ��̈�s���폜���A���Ɉ�s����
						// �܂��擪�̈�s�̍폜
						pouchDrawErea_.erase(pouchDrawErea_.begin(), pouchDrawErea_.begin() + WindowX_CellSize_);
						nowDrawPosOnPouch_.erase(nowDrawPosOnPouch_.begin(), nowDrawPosOnPouch_.begin() + WindowX_CellSize_);
						// ���Ɉ�s�ǉ��B
						/// i�̏����l		: �\���ł���ő吔 + �ǉ������ - ��
						/// for���̉����� : �\���ł���ő吔 + �ǉ�����񐔂܂�
						for (int i = DrawMaxPouchSize_ + (scrollCount_ * WindowX_CellSize_) - WindowX_CellSize_;
							i < DrawMaxPouchSize_ + (scrollCount_ * WindowX_CellSize_);
							i++)
						{
							if (i < gm.weapons.size())
							{
								pouchDrawErea_.push_back(gm.weapons[i]);
								nowDrawPosOnPouch_.push_back(weaponPosOnPouch_[i]);
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
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
				prevCursorY_ = cursorY_;
				selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;
			}
			else
			{
				if (scrollCount_ > 0)
				{
					PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
					prevCursorY_ = cursorY_;
					selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;

					scrollCount_--;
					if (pouchDrawErea_.size() == DrawMaxPouchSize_)		// �`�悳��Ă�E�B���h�E�����܂��Ă�ꍇ
					{
						pouchDrawErea_.erase(pouchDrawErea_.end() - WindowX_CellSize_, pouchDrawErea_.end());
						nowDrawPosOnPouch_.erase(nowDrawPosOnPouch_.end() - WindowX_CellSize_, nowDrawPosOnPouch_.end());
						// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
						for (int i = WindowX_CellSize_; i > 0; i--)
						{
							pouchDrawErea_.begin() = pouchDrawErea_.insert(pouchDrawErea_.begin(), gm.weapons[scrollCount_ * WindowX_CellSize_ + i - 1]);
							nowDrawPosOnPouch_.begin() = nowDrawPosOnPouch_.insert(nowDrawPosOnPouch_.begin(), weaponPosOnPouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
						}
					}
					else if (pouchDrawErea_.size() > DrawMaxPouchSize_ - WindowX_CellSize_ &&
						pouchDrawErea_.size() < DrawMaxPouchSize_)		// �`�悳��Ă�E�B���h�E�̍Ō�̈�s�ɋ󂫂�����ꍇ
					{
						pouchDrawErea_.erase(pouchDrawErea_.end() - (pouchDrawErea_.size() % WindowX_CellSize_), pouchDrawErea_.end());
						nowDrawPosOnPouch_.erase(nowDrawPosOnPouch_.end() - (nowDrawPosOnPouch_.size() % WindowX_CellSize_), nowDrawPosOnPouch_.end());
						// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
						for (int i = WindowX_CellSize_; i > 0; i--)
						{
							pouchDrawErea_.begin() = pouchDrawErea_.insert(pouchDrawErea_.begin(), gm.weapons[scrollCount_ * WindowX_CellSize_ + i - 1]);
							nowDrawPosOnPouch_.begin() = nowDrawPosOnPouch_.insert(nowDrawPosOnPouch_.begin(), weaponPosOnPouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
						}
					}
					else												// �`�悳��Ă�E�B���h�E�̉����s�����󂢂Ă���ꍇ
					{
						// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
						for (int i = WindowX_CellSize_; i > 0; i--)
						{
							pouchDrawErea_.begin() = pouchDrawErea_.insert(pouchDrawErea_.begin(), gm.weapons[scrollCount_ * WindowX_CellSize_ + i - 1]);
							nowDrawPosOnPouch_.begin() = nowDrawPosOnPouch_.insert(nowDrawPosOnPouch_.begin(), weaponPosOnPouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
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
							PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
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
						else
						{
							PlaySoundMem(Music::money_SE, DX_PLAYTYPE_BACK);
							if (Adv::day == gm.LastDay)
							{
								saleWeapons_.erase(saleWeapons_.end() - 1);
								selectWeaponPos_.erase(selectWeaponPos_.end() - 1);
								gm.money -= weaponPrice_[selectIconNum_];
								alradySelect_ = true;
							}
						}
					}
					if (!alradySelect_)
						alreadySelectWeaponPos_.push_back(selectIconNum_);
					alradySelect_ = false;
				}
			}
			else
			{
				if (Adv::day != gm.LastDay)
				{
					std::sort(selectWeaponPos_.begin(), selectWeaponPos_.end());
					for (int i = selectWeaponPos_.size() - 1; i >= 0; i--)
					{
						gm.weapons.erase(gm.weapons.begin() + selectWeaponPos_[i]);
						gm.weaponQuality.erase(gm.weaponQuality.begin() + selectWeaponPos_[i]);
					}
				}
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				saleAmount = gm.money - prevMoney_;

				if (Adv::day == gm.LastDay && saleWeapons_.size() == 0)
				{
					retryLastDay_ = true;
					if (drawalert_ && Input::GetButtonDown(PAD_INPUT_1))
					{
						dataload.Load();
						sm.LoadScene("Adv");
					}
				}
				else if (Adv::day == gm.LastDay)
					sm.LoadScene("GameClear");
				else
					sm.LoadScene("Report");
			}
		}
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

void Sale::Draw()
{
	DrawGraph(0, 0, gm.image.saleBack, TRUE);
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
			if ((signed)(x + (y * WindowX_CellSize_)) < pouchDrawErea_.size())
			{
				DrawGraph(itemX_ + x * WindowCellSize_X_, itemY_ + y * WindowCellSize_Y_, gm.image.weaponIcons[pouchDrawErea_[x + (y * WindowX_CellSize_)]], TRUE);
			}
		}
	}


	int shadowY = 0;
	int shadowX = 0;
	for (int i = 0; i < selectWeaponPos_.size(); i++)
	{
		for (int j = 0; j < nowDrawPosOnPouch_.size(); j++)
		{
			if (selectWeaponPos_[i] == nowDrawPosOnPouch_[j])
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

	SetFontSize(15);
	DrawString(OptionMenuX_, OptionMenuY_, "�������� : �J�[�\���ړ��@,�@Z�L�[ : �I�� �E �I������", gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);

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

	if (retryLastDay_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		std::string drawNextDescription = "�ŏI���͗E�҂ɕ���𔄂�Ȃ���΂����܂���B������x�������蒼���܂��B";
		int DrawWidthUnder = GetDrawStringWidth(drawNextDescription.c_str(), -1);
		DrawString((Screen::width - DrawWidthUnder) / 2, (Screen::height - (Screen::height / 4) + 30), drawNextDescription.c_str(), gm.colorWhite);
		drawalert_ = true;
	}
}
