#include "Production.h"
#include "Input.h"
#include "DataCsv.h"
#include "MyRandom.h"
#include "MyMath.h"
#include <DxLib.h>

void Production::Init()
{
	gm.itemData.Load("Resource/Datas/ItemData.csv");
	gm.weaponData.Load("Resource/Datas/WeaponData.csv");
	cursorInit_ = true;

	for (int i = CsvSkipCell_; i < gm.weaponData[0].size(); i++)
	{
		weaponName_.push_back(gm.weaponData[0][i]);
	}
}

void Production::Final()
{

}

void Production::Update()
{
	/*----- �쐬����I�� -----*/
	if (!recipeSelection_)
	{
		if (cursorInit_) // �J�[�\���ʒu������
		{
			cursorX_ = CursorX_Min_RecipeSelection_;
			cursorY_ = CursorY_Min_RecipeSelection_;
			weaponID_ = 0;
			cursorInit_ = false;
		}

		/*----- �J�[�\���ړ� -----*/
		if (Input::GetButtonDown(PAD_INPUT_RIGHT))
		{
			if (cursorX_ < CursorX_Max_RecipeSelection_)
			{
				cursorX_ = CursorX_Max_RecipeSelection_;
				prevCursorY_ = cursorY_;
				weaponID_++;
			}
			else
			{
				cursorX_ = CursorX_ProceedNextPart_;
				cursorY_ = CursorY_ProceedNextPart_;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_LEFT))
		{
			if (cursorX_ > CursorX_Min_RecipeSelection_ && cursorX_ != CursorX_ProceedNextPart_)
			{
				cursorX_ = CursorX_Min_RecipeSelection_;
				weaponID_--;
			}
			else if (cursorX_ == CursorX_ProceedNextPart_)
			{
				cursorX_ = CursorX_Max_RecipeSelection_;
				cursorY_ = prevCursorY_;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_DOWN) &&
			cursorY_ != CursorY_Max_RecipeSelection_ &&
			cursorX_ <= CursorX_Max_RecipeSelection_)
		{
			cursorY_ += CursorY_MoveVerticalWidth_RecipeSelect_;
			prevCursorY_ = cursorY_;
			weaponID_ += WeaponID_ByLineBreak_RecipeSelection_;
		}
		if (Input::GetButtonDown(PAD_INPUT_UP) &&
			cursorY_ != CursorY_Min_RecipeSelection_ &&
			cursorX_ <= CursorX_Max_RecipeSelection_)
		{
			cursorY_ -= CursorY_MoveVerticalWidth_RecipeSelect_;
			weaponID_ -= WeaponID_ByLineBreak_RecipeSelection_;
		}
		/*---------------*/

		/*----- ��镐������� -----*/
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			if (cursorX_ == CursorX_ProceedNextPart_ && cursorY_ == CursorY_ProceedNextPart_)
			{
				sm.LoadScene("Sale");
			}
			else
			{
				if (canWeaponMake_[weaponID_ / 2])					// �I���������킪����Ȃ�
				{
					recipeSelection_ = true;						// �t���O�𗧂Ă�

					if (cursorY_ <= CursorY_Max_RecipeSelection_ / 2) // �ؐ�����I��
					{
						ItemType_ = gm.itemData[CsvTypeCheck_][CsvSkipCell_];
						cursorInit_ = true;
					}
					else											  // �ΐ�����I��
					{
						ItemType_ = gm.itemData[CsvTypeCheck_][gm.itemData[0].size() - 1];
						cursorInit_ = true;
					}
				}
			}
		}
		/*---------------*/
	}

	/*---------------*/

	/*----- �g�p�f�ޑI�� -----*/
	else
	{
		if (!weaponMakeAssert_)
		{
			if (cursorInit_) // �J�[�\���ʒu������
			{
				cursorX_ = CursorX_Min_ItemSelect_;
				cursorY_ = CursorY_Min_ItemSelect_;
				selectIconNum_ = 0;
				cursorInit_ = false;

				// �����蕔���őI���ł�����̂�vector�ɕۊ�
				GetHandleForWeaponMake();
			}

			/*----- �J�[�\���ړ� -----*/

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
					if (itemForWeaponMake_.size() > DrawMaxPouchSize_)
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
								if (i < itemForWeaponMake_.size())
								{
									PouchDrawErea_.push_back(itemForWeaponMake_[i]);
									NowDrawPosOnPouch_.push_back(ItemPosOnThePouch_[i]);
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
								PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), itemForWeaponMake_[scrollCount_ * WindowX_CellSize_ + i - 1]);
								NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), ItemPosOnThePouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
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
								PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), itemForWeaponMake_[scrollCount_ * WindowX_CellSize_ + i - 1]);
								NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), ItemPosOnThePouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
							}
						}
						else												// �`�悳��Ă�E�B���h�E�̉����s�����󂢂Ă���ꍇ
						{
							// �`�悷��A�C�e����vector�̍ŏ��ɕ`�悳��ĂȂ���s���ǉ�
							for (int i = WindowX_CellSize_; i > 0; i--)
							{
								PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), itemForWeaponMake_[scrollCount_ * WindowX_CellSize_ + i - 1]);
								NowDrawPosOnPouch_.begin() = NowDrawPosOnPouch_.insert(NowDrawPosOnPouch_.begin(), ItemPosOnThePouch_[scrollCount_ * WindowX_CellSize_ + i - 1]);
							}
						}
					}
				}
			}

			/*---------------*/

			/*----- �����蕔���f�ޑI�� -----*/
			if (!shouldWeaponMainCreate_)
			{
				if (Input::GetButtonDown(PAD_INPUT_1))
				{
					if (cursorX_ <= CursorX_Max_ItemSelect_)
					{
						if (selectIconNum_ < itemForWeaponMake_.size())
						{
							if (gm.handles.size() < HandleSelect_MaxSize_ && !AlreadySecectItem(ItemPosOnThePouch_[selectIconNum_])) // �d�����Ă��Ȃ�������
							{
								gm.handles.push_back(itemForWeaponMake_[selectIconNum_]);
								gm.handlesQuality.push_back(itemQualityForWeaponMake_[selectIconNum_]);
								SelectItemPosOnThePouch_.push_back(NowDrawPosOnPouch_[selectIconNum_ - scrollCount_ * WindowX_CellSize_]);
							}
							else
							{
								for (int i = 0; i < gm.handles.size(); i++)
								{
									if (SelectItemPosOnThePouch_[i] == NowDrawPosOnPouch_[selectIconNum_ - scrollCount_ * WindowX_CellSize_])
									{
										gm.handles.erase(gm.handles.begin() + i);
										gm.handlesQuality.erase(gm.handlesQuality.begin() + i);
										SelectItemPosOnThePouch_.erase(SelectItemPosOnThePouch_.begin() + i);
									}
								}
							}
						}
					}
					// ����
					else
					{
						if (HandleSlectOk_)
						{
							cursorX_ = CursorX_Min_ItemSelect_;			// �J�[�\���ʒu������
							cursorY_ = CursorY_Min_ItemSelect_;
							selectIconNum_ = 0;							// �I�𒆂̔ԍ�������
							shouldWeaponMainCreate_ = true;
							itemDetail_ = false;						// �A�C�e���ڍ׃E�B���h�E�t���O������
							itemForWeaponMake_.clear();					// �I���ł���A�C�e�����X�g���N���A
							ItemPosOnThePouch_.clear();					// �I���ł���A�C�e���|�[�`���̈ʒu�����N���A

							// ���C�������őI���ł�����̂�vector�ɕۊ�
							GetMainForWeaponMake(ItemType_);
						}
						else
						{
							weaponMakeAssert_ = true;
						}
					}
				}

				if (gm.handles.size() >= 1)
				{
					HandleSlectOk_ = true;
				}
				else
				{
					HandleSlectOk_ = false;
				}

				if (Input::GetButtonDown(PAD_INPUT_3) && selectIconNum_ < itemForWeaponMake_.size())
				{
					if (!itemDetail_)
						itemDetail_ = true;
					else
						itemDetail_ = false;
				}

				// �ڍ׃E�B���h�E�\�������܂܃J�[�\���ړ����Ă�����悤��
				if (selectIconNum_ >= itemForWeaponMake_.size())
					itemDetail_ = false;

				if (Input::GetButtonDown(PAD_INPUT_2))
				{
					Format();
				}
			}

			/*----- ���C�������f�ޑI�� -----*/
			else
			{
				if (Input::GetButtonDown(PAD_INPUT_1))
				{
					if (cursorX_ <= CursorX_Max_ItemSelect_)
					{
						if (selectIconNum_ < itemForWeaponMake_.size())
						{
							if (gm.main.size() < MainSelect_MaxSize_ && !AlreadySecectItem(ItemPosOnThePouch_[selectIconNum_])) // �d�����Ă��Ȃ�������
							{
								gm.main.push_back(itemForWeaponMake_[selectIconNum_]);
								gm.mainQuality.push_back(itemQualityForWeaponMake_[selectIconNum_]);
								SelectItemPosOnThePouch_.push_back(NowDrawPosOnPouch_[selectIconNum_ - scrollCount_ * WindowX_CellSize_]);
							}
							else
							{
								for (int i = 0; i < gm.main.size(); i++)
								{
									if (SelectItemPosOnThePouch_[i + gm.handles.size()] == ItemPosOnThePouch_[selectIconNum_])
									{
										for (int j = 0; j < gm.handles.size(); j++)
										{
											if (SelectItemPosOnThePouch_[j] != NowDrawPosOnPouch_[selectIconNum_ - scrollCount_ * WindowX_CellSize_])
											{
												gm.main.erase(gm.main.begin() + i);
												gm.mainQuality.erase(gm.mainQuality.begin() + i);
												SelectItemPosOnThePouch_.erase(SelectItemPosOnThePouch_.begin() + (i + gm.handles.size()));
												break;
											}
										}
									}
								}
							}
						}
					}
					else
					{
						bool roopBreak = false;
						for (int i = 0; i < gm.handles.size(); i++)
						{
							for (int j = 0; j < gm.main.size(); j++)
							{   // ���C�������I����A�K�v�f�ނ��܂܂�Ă�����
								if (MainSlectOk_ &&
									((int)gm.weaponData[CsvNecessaryItem_][weaponID_ + CsvSkipCell_] == gm.handles[i] ||
										(int)gm.weaponData[CsvNecessaryItem_][weaponID_ + CsvSkipCell_] == gm.main[j]))
								{
									shouldCreate_ = true;
									itemDetail_ = false;
									weaponMakeAssert_ = false;
									roopBreak = true;
									itemForWeaponMake_.clear();			// �I���ł���A�C�e�����X�g���N���A
									ItemPosOnThePouch_.clear();			// �I���ł���A�C�e���|�[�`���̈ʒu�����N���A
									break;
								}
								else
								{
									weaponMakeAssert_ = true;
								}
							}
							if (roopBreak)
								break;
						}
					}
				}

				if (gm.main.size() >= 2)
				{
					MainSlectOk_ = true;
				}
				else
				{
					MainSlectOk_ = false;
				}

				if (Input::GetButtonDown(PAD_INPUT_3) && selectIconNum_ < itemForWeaponMake_.size())
				{
					if (!itemDetail_)
						itemDetail_ = true;
					else
						itemDetail_ = false;
				}

				// �ڍ׃E�B���h�E�\�������܂܃J�[�\���ړ����Ă�����悤��
				if (selectIconNum_ >= itemForWeaponMake_.size())
					itemDetail_ = false;

				if (Input::GetButtonDown(PAD_INPUT_2))
				{
					shouldWeaponMainCreate_ = false;
					gm.main.clear();
					gm.main.shrink_to_fit();
					gm.mainQuality.clear();
					gm.mainQuality.shrink_to_fit();
					itemForWeaponMake_.clear();
					itemForWeaponMake_.shrink_to_fit();
					ItemPosOnThePouch_.clear();
					ItemPosOnThePouch_.shrink_to_fit();
					SelectItemPosOnThePouch_.erase
					(SelectItemPosOnThePouch_.begin() + gm.handles.size(),
					 SelectItemPosOnThePouch_.end());
					SelectItemPosOnThePouch_.shrink_to_fit();

					// �����蕔���őI���ł�����̂�vector�ɕۊ�
					GetHandleForWeaponMake();
				}
			}

			/*----------*/

			/*----- �f�ޑI����B���퐶�� -----*/
			if (shouldCreate_)
			{
				if (MainSlectOk_)
				{
					// vector���e�N���A�O�ɕi�����v�Z���ĕۊǂ��Ă����B
					// �ꎞ�I�ɕۊǂ��Ă�gm.handles��gm.main�̓��e���N���A����B
					// gm.pouch��gm.lumber���玝���胊�X�g�ɓ����Ă���́A
					// gm.pouch��gm.���C�������̃��X�g���烁�C���������X�g�ɓ����Ă���̂������A
					// waponID�̕���������
					// gm.waponQuality�ɕi������

					int weaponQualityStorage = 0; // �i���ۑ��p�ϐ�

					for (int i = 0; i < gm.handles.size(); i++)
					{
						weaponQualityStorage += (gm.handlesQuality[i] / ((i + 1) * 2)); // �S�f�ނ̕i�����v�Z(�����蕔��)
					}
					for (int i = 0; i < gm.main.size(); i++)
					{
						weaponQualityStorage += (gm.mainQuality[i] / ((i + 1) * 2));	// �S�f�ނ̕i�����v�Z(��Ōv�Z���������蕔�� + ���C������)
					}

					if (!animationEnd_ && !MakeEnd_)
					{
						for (int i = 0; i < gm.handles.size(); i++)
							drawItemID_.push_back(gm.handles[i]);
						for (int i = 0; i < gm.main.size(); i++)
							drawItemID_.push_back(gm.main[i]);

						for (int i = 0; i < drawItemID_.size(); i++)
						{
							animationX_.push_back(0);
							animationY_.push_back(0);
						}

						MakeEnd_ = true;
					}
					if (!MakeEnd_)
					{
						/*----- �I���ςݑf�ލ폜���� -----*/

						/*�@�I���ς݂̃A�C�e���̃|�[�`�ɂ�����ʒu�������Ă�Vector���@*/
						/*�@�@�@�@�~���Ƀ\�[�g����gm.pouch�̌�납�珇��erase�@ �@�@�@*/

						std::sort(SelectItemPosOnThePouch_.begin(), SelectItemPosOnThePouch_.end(), std::greater<int>());
						for (int i = 0; i < SelectItemPosOnThePouch_.size(); i++)
						{
							gm.pouch.erase(gm.pouch.begin() + SelectItemPosOnThePouch_[i]);
							gm.pouchQuality.erase(gm.pouchQuality.begin() + SelectItemPosOnThePouch_[i]);

						}
						/*---------------*/

						gm.handles.clear();
						gm.handles.shrink_to_fit();
						gm.main.clear();
						gm.main.shrink_to_fit();

						gm.weapons.push_back(weaponID_);
						gm.weaponQuality.push_back(weaponQualityStorage);
					}
				}
				else
					shouldRetry_ = true;
				if (!MakeEnd_)
				{// ������
					Format();
				}
			}
		}

		else
		{
			if (Input::GetButtonDown(PAD_INPUT_1))
			{
				weaponMakeAssert_ = false;
			}
		}
	}
}

void Production::Format()
{
	// �t���O��������
	cursorInit_ = true;
	shouldWeaponMainCreate_ = false;
	recipeSelection_ = false;
	shouldCreate_ = false;
	itemDetail_ = false;
	MakeEnd_ = false;
	animationEnd_ = false;
	// ���X�g���N���A(������)
	gm.handles.clear();
	gm.handles.shrink_to_fit();
	gm.handlesQuality.clear();
	gm.handlesQuality.shrink_to_fit();
	gm.main.clear();
	gm.main.shrink_to_fit();
	gm.mainQuality.clear();
	gm.mainQuality.shrink_to_fit();
	itemForWeaponMake_.clear();
	itemForWeaponMake_.shrink_to_fit();
	itemQualityForWeaponMake_.clear();
	itemQualityForWeaponMake_.shrink_to_fit();
	SelectItemPosOnThePouch_.clear();
	SelectItemPosOnThePouch_.shrink_to_fit();
	ItemPosOnThePouch_.clear();
	ItemPosOnThePouch_.shrink_to_fit();
	weaponName_.clear();
	weaponName_.shrink_to_fit();
	// CSV��j��
	gm.itemData.clear();
	gm.weaponData.clear();
	// �ŏ��ɖ߂�
	Init();
}

void Production::Draw()
{
	DrawGraph(0, 0, Image::productionBack, TRUE);

	/*-----�f�ޑI�����`��-----*/
	if (recipeSelection_ && !MakeEnd_)
	{
		DrawGraph(WindowX_, WindowY_, Image::itemWindow, TRUE);
		DrawGraph(SelectItemWindowX_, WindowY_, Image::selectItemWindow, TRUE);
		DrawGraph(NextButtonX_, NextButtonY_, Image::next, TRUE);

		for (int y = 0; y < WindowY_CellSize_; y++)
		{
			for (int x = 0; x < WindowX_CellSize_; x++)
			{
				if ((x + (y * WindowX_CellSize_)) < PouchDrawErea_.size())
				{
					DrawGraph(itemX_ + x * WindowCellSize_X_, itemY_ + y * WindowCellSize_Y_, Image::itemIcons[PouchDrawErea_[x + (y * WindowX_CellSize_)]], TRUE);
				}
			}
		}


		int shadowY = 0;
		int shadowX = 0;
		for (int i = 0; i < SelectItemPosOnThePouch_.size(); i++)
		{
			for (int j = 0; j < NowDrawPosOnPouch_.size(); j++)
			{
				if (SelectItemPosOnThePouch_[i] == NowDrawPosOnPouch_[j])
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

		// �K�v�f�ނ̕`��
		DrawGraph(AlreadySelect_MainItem_X_, MakeWeaponY_, Image::itemIcons[(int)gm.weaponData[CsvNecessaryItem_][weaponID_ + CsvSkipCell_]], TRUE);

		// ��镐��̕`��
		DrawGraph(MakeWeaponX_, MakeWeaponY_, Image::weaponIcons[weaponID_], TRUE);

		/*----- �����蕔���̑f�ޕ`�� -----*/

		for (int i = 0; i < gm.handles.size(); i++)
		{
			if (gm.handles.size() > 0)
			{
				// �I���������̂�`��
				DrawGraph
				(AlreadySelect_HandleItem_X_ + i * AlreadySelect_HandleItem_X_Diameter_,
					AlreadySelect_HandleItem_Y_,
					Image::itemIcons[gm.handles[i]],
					TRUE);
			}
		}
		/*---------------*/

		/*----- ���C�������̑f�ޕ`�� -----*/

		for (int i = 0; i < gm.main.size(); i++)
		{
			if (gm.main.size() > 0)
			{
				// �I���������̂�`��
				DrawGraph
				(AlreadySelect_MainItem_X_ + i * AlreadySelect_MainItem_X_Diameter_,
					AlreadySelect_MainItem_Y_,
					Image::itemIcons[gm.main[i]],
					TRUE);
			}
		}
		/*---------------*/

		if (cursorX_ >= CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
			DrawGraph(cursorX_, cursorY_, Image::itemSelection, TRUE);

		if (cursorX_ > CursorX_Max_ItemSelect_)
			DrawGraph(cursorX_, cursorY_, Image::nextCursor, TRUE);

		/*----- �A�C�e���̏ڍ׏�� -----*/
		if (itemDetail_)
		{
			DrawGraph(DetailWindowX_, DetailWindowY_, Image::detailWindow, TRUE);
			DrawString(ItemNameX_, ItemNameY_, gm.itemData[0][itemForWeaponMake_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
			std::stringstream ss;
			ss << itemQualityForWeaponMake_[selectIconNum_];
			DrawString(ItemQualityX_, ItemNameY_, ("�i�� : " + ss.str()).c_str(), gm.colorWhite);								// �i�� : 123(vector<int> -> char�ɕϊ�)�@�ɂ������B�����p����
			DrawString(ItemInfoX_, ItemInfoY_, gm.itemData[1][itemForWeaponMake_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);

		}

		/*---------------*/
	}

	/*---------------*/

	/*-----�쐬����I�����`��-----*/
	else if (!recipeSelection_ && !MakeEnd_)
	{
		DrawGraph(NextButtonX_, NextButtonY_, Image::end, TRUE);

		DrawGraph(WindowX_, RecipeWindowX_, Image::recipeWindow, TRUE);

		for (int i = 0; i < canWeaponMake_.size(); i++)
		{
			if (canWeaponMake_[i])
			{
				DrawString(DrawWeaponName_LeftLine_X_, DrawWeaponName_Y_ + (CursorY_MoveVerticalWidth_RecipeSelect_ * i), weaponName_[i * 2].c_str(), gm.colorWhite);
				DrawString(DrawWeaponName_RightLine_X_, DrawWeaponName_Y_ + (CursorY_MoveVerticalWidth_RecipeSelect_ * i), weaponName_[i * 2 + 1].c_str(), gm.colorWhite);
			}
		}

		if (cursorX_ < CursorX_ProceedNextPart_)
			DrawGraph(cursorX_, cursorY_, Image::recipeSelection, TRUE);
		else
			DrawGraph(cursorX_, cursorY_, Image::nextCursor, TRUE);
	}

	/*---------------*/

	/*-----�i���`��-----*/
	if (!MakeEnd_)
	{
		int drawWeaponQualityStorage = 0; // �i���ۑ��p�ϐ�

		for (int i = 0; i < gm.handles.size(); i++)
		{
			drawWeaponQualityStorage += (gm.handlesQuality[i] / ((i + 1) * 2)); // �S�f�ނ̕i�����v�Z(�����蕔��)
		}
		for (int i = 0; i < gm.main.size(); i++)
		{
			drawWeaponQualityStorage += (gm.mainQuality[i] / ((i + 1) * 2));	// �S�f�ނ̕i�����v�Z(��Ōv�Z���������蕔�� + ���C������)
		}

		DrawString(MakeWeaponQualityX_, MakeWeaponQualityY_, std::to_string(drawWeaponQualityStorage).c_str(), gm.colorWhite);
	}

	/*---------------*/

	if (weaponMakeAssert_)
	{
		std::string drawMassege = "�f�ސ�������Ȃ����A�K�v�f�ނ��I������Ă��܂���B";
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
		DrawBox(0, 0, Screen::Width, Screen::Height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::Width - DrawWidth) / 2, Screen::Height / 2, drawMassege.c_str(), gm.colorWhite);
		drawMassege = "Z�L�[�Ŗ߂�";
		DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::Width - DrawWidth) / 2, (Screen::Height - (Screen::Height / 4)), drawMassege.c_str(), gm.colorWhite);
	}

	/*-----�f�ޑI���㕐�퐶���A�j���[�V����-----*/
	if (MakeEnd_)
	{
		if (drawCounter_ > 0)
		{
			for (int i = 0; i < drawItemID_.size(); i++)
			{
				animationX_[i] = (Screen::Width / 2) + cos((std::abs(angle_) / drawItemID_.size()) * (i + 1) * MyMath::Deg2Rad) * distToCenter_;
				animationY_[i] = (Screen::Height / 2) + sin((std::abs(angle_) / drawItemID_.size()) * (i + 1) * MyMath::Deg2Rad) * distToCenter_;

				angle_ += 10;
			}

			for (int i = 0; i < drawItemID_.size(); i++)
				DrawGraph(animationX_[i], animationY_[i], Image::itemIcons[drawItemID_[i]], TRUE);

			distToCenter_--;
			drawCounter_--;
		}
		else
		{
			DrawGraph(Screen::Width / 2, Screen::Height / 2, Image::weaponIcons[weaponID_], TRUE);
			std::string drawMassege = "Z�L�[�Ŏ���";
			int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
			DrawString((Screen::Width - DrawWidth) / 2, (Screen::Height - (Screen::Height / 4)), drawMassege.c_str(), gm.colorWhite);

			if (Input::GetButtonDown(PAD_INPUT_1))
			{
				MakeEnd_ = false;
				animationEnd_ = true;
				distToCenter_ = defaultDrawCount_;
				drawCounter_ = defaultDrawCount_;
				angle_ = defaultAngle_;
			}
		}
	}

	/*---------------*/

}

void Production::GetHandleForWeaponMake()
{
	PouchDrawErea_.clear();
	NowDrawPosOnPouch_.clear();

	for (int i = 0; i < gm.pouch.size(); i++)
	{
		if ((int)gm.itemData[CsvTypeCheckFine_][gm.pouch[i] + CsvSkipCell_] == lumberNum_)
		{
			itemForWeaponMake_.push_back(gm.pouch[i]);
			itemQualityForWeaponMake_.push_back(gm.pouchQuality[i]);
			ItemPosOnThePouch_.push_back(i);
			if (PouchDrawErea_.size() < DrawMaxPouchSize_)
				PouchDrawErea_.push_back(gm.pouch[i]);
			if (NowDrawPosOnPouch_.size() < DrawMaxPouchSize_)
				NowDrawPosOnPouch_.push_back(i);
		}
	}
}

void Production::GetMainForWeaponMake(int ItemType)
{
	PouchDrawErea_.clear();
	NowDrawPosOnPouch_.clear();

	for (int i = 0; i < gm.pouch.size(); i++)
	{
		if ((int)gm.itemData[CsvTypeCheck_][gm.pouch[i] + CsvSkipCell_] == ItemType)
		{
			itemForWeaponMake_.push_back(gm.pouch[i]);
			itemQualityForWeaponMake_.push_back(gm.pouchQuality[i]);
			ItemPosOnThePouch_.push_back(i);
			if (PouchDrawErea_.size() < DrawMaxPouchSize_)
				PouchDrawErea_.push_back(gm.pouch[i]);
			if (NowDrawPosOnPouch_.size() < DrawMaxPouchSize_)
				NowDrawPosOnPouch_.push_back(i);
		}
	}
}

bool Production::AlreadySecectItem(int ItemPosOnPouch)
{
	for (int i = 0; i < (unsigned)SelectItemPosOnThePouch_.size(); i++)
	{
		if (ItemPosOnPouch == SelectItemPosOnThePouch_[i])
			return true;
	}
	return false;
}


