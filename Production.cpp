#include "Production.h"
#include "Input.h"
#include "DataCsv.h"
#include "MyRandom.h"
#include "MyMath.h"
#include "Adv.h"
#include "Music.h"
#include <DxLib.h>

bool Production::canWoodSword_ = true;
bool Production::canJawaSword_ = true;
bool Production::canEnriSword_ = false;
bool Production::canKeinSword_ = false;
bool Production::canShizukuSword_ = false;
bool Production::canSaintSword_ = false;
bool Production::canGodWoodSword_ = false;

bool Production::canStoneSword_ = true;
bool Production::canIronOreSword_ = true;
bool Production::canJadeSword_ = false;
bool Production::canDiamondSword_ = false;
bool Production::canCarbonadeSword_ = false;
bool Production::canOrichalcumSword_ = false;
bool Production::canGodStoneSword_ = false;

std::vector<bool> Production::canWeaponMake_{ canWoodSword_     , canJawaSword_      , canEnriSword_    , canKeinSword_,
                                              canShizukuSword_  , canSaintSword_     , canGodWoodSword_ ,
                                              canStoneSword_    , canIronOreSword_   , canJadeSword_    , canDiamondSword_,
                                              canCarbonadeSword_, canOrichalcumSword_, canGodStoneSword_ };

void Production::Init()
{
	gm.image.Load(tag);

	gm.itemData.Load("Resource/Datas/ItemData.csv");
	gm.weaponData.Load("Resource/Datas/WeaponData.csv");
	cursorInit_ = true;

	cursorX_ = CursorX_Min_RecipeSelection_;
	cursorY_ = CursorY_Min_RecipeSelection_;

	for (int i = CsvSkipCell_; i < gm.weaponData[0].size(); i++)
	{
		weaponName_.push_back(gm.weaponData[0][i]);
	}

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
	/*----- �쐬����I�� -----*/
	if (!recipeSelection_ && is_Operation_Description_Been_)
	{
		if (cursorInit_) // �J�[�\���ʒu������
		{
			cursorX_  = CursorX_Min_RecipeSelection_;
			cursorY_  = CursorY_Min_RecipeSelection_;
			weaponID_ = 0;
			cursorInit_ = false;
		}

		/*----- �J�[�\���ړ� -----*/
		if (Input::GetButtonDown(PAD_INPUT_RIGHT))
		{
			if (cursorX_ < CursorX_Max_RecipeSelection_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_     = CursorX_Max_RecipeSelection_;
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
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ = CursorX_Min_RecipeSelection_;
				weaponID_--;
			}
			else if (cursorX_ == CursorX_ProceedNextPart_)
			{
				PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
				cursorX_ = CursorX_Max_RecipeSelection_;
				cursorY_ = prevCursorY_;
			}
		}
		if (Input::GetButtonDown(PAD_INPUT_DOWN) &&
			cursorY_ != CursorY_Max_RecipeSelection_ &&
			cursorX_ <= CursorX_Max_RecipeSelection_)
		{
			PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
			cursorY_ += CursorY_MoveVerticalWidth_RecipeSelect_;
			prevCursorY_ = cursorY_;
			weaponID_ += WeaponID_ByLineBreak_RecipeSelection_;
		}
		if (Input::GetButtonDown(PAD_INPUT_UP) &&
			cursorY_ != CursorY_Min_RecipeSelection_ &&
			cursorX_ <= CursorX_Max_RecipeSelection_)
		{
			PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
			cursorY_ -= CursorY_MoveVerticalWidth_RecipeSelect_;
			weaponID_ -= WeaponID_ByLineBreak_RecipeSelection_;
		}
		/*---------------*/

		/*----- ��镐������� -----*/
		if (Input::GetButtonDown(PAD_INPUT_1))
		{
			if (cursorX_ == CursorX_ProceedNextPart_ && cursorY_ == CursorY_ProceedNextPart_)
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				sm.LoadScene("Sale");
			}
			else
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				if (canWeaponMake_[weaponID_ / 2])                  // �I���������킪����Ȃ�
				{
					recipeSelection_ = true;                        // �t���O�𗧂Ă�

					if (weaponID_ < canWeaponMake_.size())          // �ؐ�����I��
					{
						ItemType_ = gm.itemData[CsvTypeCheck_][CsvSkipCell_];
						cursorInit_ = true;
					}
					else                                            // �ΐ�����I��
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
	else if (is_Operation_Description_Been_)
	{
		if (!weaponMakeAssert_)
		{
			if (cursorInit_) // �J�[�\���ʒu������
			{
				cursorX_       = CursorX_Min_ItemSelect_;
				cursorY_       = CursorY_Min_ItemSelect_;
				selectIconNum_ = 0;
				cursorInit_    = false;

				// �����蕔���őI���ł�����̂�vector�ɕۊ�
				GetHandleForWeaponMake();
			}

			/*----- �J�[�\���ړ� -----*/

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
				else if (cursorX_ <= CursorX_Max_ItemSelect_)
				{
					if (itemForWeaponMake_.size() > DrawMaxPouchSize_)
					{
						if (PouchDrawErea_.size() > WindowX_CellSize_)
						{
							PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
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
					PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
					cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
					prevCursorY_ = cursorY_;
					selectIconNum_ -= ItemID_ByLineBreak_ItemSelect_;
				}
				else if (cursorX_ <= CursorX_Max_ItemSelect_)
				{
					if (scrollCount_ > 0)
					{
						PlaySoundMem(Music::cursormove_SE, DX_PLAYTYPE_BACK);
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
							PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
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
							PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
							cursorX_ = CursorX_Min_ItemSelect_;			// �J�[�\���ʒu������
							cursorY_ = CursorY_Min_ItemSelect_;
							selectIconNum_ = 0;							// �I�𒆂̔ԍ�������
							shouldWeaponMainCreate_ = true;
							itemDetail_ = false;						// �A�C�e���ڍ׃E�B���h�E�t���O������
							itemForWeaponMake_.clear();					// �I���ł���A�C�e�����X�g���N���A
							itemQualityForWeaponMake_.clear();
							ItemPosOnThePouch_.clear();					// �I���ł���A�C�e���|�[�`���̈ʒu�����N���A

							// ���C�������őI���ł�����̂�vector�ɕۊ�
							GetMainForWeaponMake(ItemType_);
						}
						else
						{
							PlaySoundMem(Music::error_SE, DX_PLAYTYPE_BACK);
							weaponMakeAssert_ = true;
						}
					}
				}

				if (Input::GetButtonDown(PAD_INPUT_2))
				{
					PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
					Format();
				}

				if (Input::GetButtonDown(PAD_INPUT_3) && selectIconNum_ < itemForWeaponMake_.size())
				{
					PlaySoundMem(Music::menuopen_SE, DX_PLAYTYPE_BACK);
					if (!itemDetail_)
						itemDetail_ = true;
					else
						itemDetail_ = false;
				}

				if (gm.handles.size() >= 1)
				{
					HandleSlectOk_ = true;
				}
				else
				{
					HandleSlectOk_ = false;
				}

				// �ڍ׃E�B���h�E�\�������܂܃J�[�\���ړ����Ă�����悤��
				if (selectIconNum_ >= itemForWeaponMake_.size())
					itemDetail_ = false;
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
							PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
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
									PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
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
									PlaySoundMem(Music::error_SE, DX_PLAYTYPE_BACK);
									weaponMakeAssert_ = true;
								}
							}
							if (roopBreak)
								break;
						}
					}
				}

				if (Input::GetButtonDown(PAD_INPUT_2))
				{
					PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
					shouldWeaponMainCreate_ = false;
					gm.main.clear();
					gm.mainQuality.clear();
					itemForWeaponMake_.clear();
					ItemPosOnThePouch_.clear();
					SelectItemPosOnThePouch_.erase
					(SelectItemPosOnThePouch_.begin() + gm.handles.size(),
						SelectItemPosOnThePouch_.end());

					// �����蕔���őI���ł�����̂�vector�ɕۊ�
					GetHandleForWeaponMake();
				}

				if (Input::GetButtonDown(PAD_INPUT_3) && selectIconNum_ < itemForWeaponMake_.size())
				{
					PlaySoundMem(Music::menuopen_SE, DX_PLAYTYPE_BACK);
					if (!itemDetail_)
						itemDetail_ = true;
					else
						itemDetail_ = false;
				}

				if (gm.main.size() >= 2)
				{
					MainSlectOk_ = true;
				}
				else
				{
					MainSlectOk_ = false;
				}

				// �ڍ׃E�B���h�E�\�������܂܃J�[�\���ړ����Ă�����悤��
				if (selectIconNum_ >= itemForWeaponMake_.size())
					itemDetail_ = false;
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

						/*�@�I���ς݂̃A�C�e���̃|�[�`�ɂ�����ʒu�������Ă�vector���@*/
						/*�@�@�@�@�~���Ƀ\�[�g����gm.pouch�̌�납�珇��erase�@ �@�@�@*/

						std::sort(SelectItemPosOnThePouch_.begin(), SelectItemPosOnThePouch_.end(), std::greater<int>());
						for (int i = 0; i < SelectItemPosOnThePouch_.size(); i++)
						{
							gm.pouch.erase(gm.pouch.begin() + SelectItemPosOnThePouch_[i]);
							gm.pouchQuality.erase(gm.pouchQuality.begin() + SelectItemPosOnThePouch_[i]);

						}
						/*---------------*/

						gm.handles.clear();
						gm.handlesQuality.clear();
						gm.main.clear();
						gm.mainQuality.clear();

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
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				weaponMakeAssert_ = false;
			}
		}
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
}

void Production::Format()
{
	scrollCount_ = 0;
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
	gm.handlesQuality.clear();
	gm.main.clear();
	gm.mainQuality.clear();
	itemForWeaponMake_.clear();
	itemQualityForWeaponMake_.clear();
	SelectItemPosOnThePouch_.clear();
	ItemPosOnThePouch_.clear();
	weaponName_.clear();
	// CSV��j��
	gm.itemData.clear();
	gm.weaponData.clear();
	// �ŏ��ɖ߂�
	Init();
}

void Production::Draw()
{
	DrawGraph(0, 0, gm.image.productionBack, TRUE);

	/*-----�f�ޑI�����`��-----*/
	if (recipeSelection_ && !MakeEnd_)
	{
		DrawGraph(WindowX_, WindowY_, gm.image.itemWindow, TRUE);
		DrawGraph(SelectItemWindowX_, WindowY_, gm.image.selectItemWindow, TRUE);
		DrawGraph(NextButtonX_, NextButtonY_, gm.image.next, TRUE);

		for (int y = 0; y < WindowY_CellSize_; y++)
		{
			for (int x = 0; x < WindowX_CellSize_; x++)
			{
				if ((x + (y * WindowX_CellSize_)) < PouchDrawErea_.size())
				{
					DrawGraph(itemX_ + x * WindowCellSize_X_, itemY_ + y * WindowCellSize_Y_, gm.image.itemIcons[PouchDrawErea_[x + (y * WindowX_CellSize_)]], TRUE);
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
		DrawGraph(AlreadySelect_MainItem_X_, MakeWeaponY_, gm.image.itemIcons[(int)gm.weaponData[CsvNecessaryItem_][weaponID_ + CsvSkipCell_]], TRUE);

		// ��镐��̕`��
		DrawGraph(MakeWeaponX_, MakeWeaponY_, gm.image.weaponIcons[weaponID_], TRUE);

		/*----- �����蕔���̑f�ޕ`�� -----*/

		for (int i = 0; i < gm.handles.size(); i++)
		{
			if (gm.handles.size() > 0)
			{
				// �I���������̂�`��
				DrawGraph
				(AlreadySelect_HandleItem_X_ + i * AlreadySelect_HandleItem_X_Diameter_,
					AlreadySelect_HandleItem_Y_,
					gm.image.itemIcons[gm.handles[i]],
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
					gm.image.itemIcons[gm.main[i]],
					TRUE);
			}
		}
		/*---------------*/

		if (cursorX_ >= CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
			DrawGraph(cursorX_, cursorY_, gm.image.itemSelection, TRUE);

		if (cursorX_ > CursorX_Max_ItemSelect_)
			DrawGraph(cursorX_, cursorY_, gm.image.nextCursor, TRUE);

		/*----- �A�C�e���̏ڍ׏�� -----*/
		if (itemDetail_)
		{
			DrawGraph(DetailWindowX_, DetailWindowY_, gm.image.detailWindow, TRUE);
			DrawString(ItemNameX_, ItemNameY_, gm.itemData[0][itemForWeaponMake_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
			std::stringstream ss;
			ss << itemQualityForWeaponMake_[selectIconNum_ + scrollCount_ * WindowX_CellSize_];
			DrawString(ItemQualityX_, ItemNameY_, ("�i�� : " + ss.str()).c_str(), gm.colorWhite);								// �i�� : 123(vector<int> -> char�ɕϊ�)�@�ɂ������B�����p����
			DrawString(ItemInfoX_, ItemInfoY_, gm.itemData[1][itemForWeaponMake_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);

		}

		/*---------------*/
		SetFontSize(15);
		DrawString(OptionMenuX_, OptionMenuY_, "�������� : �J�[�\���ړ��@,�@Z�L�[ : �I�� �E �I�������@,�@X�L�[ : ��O��  ,  C�L�[ : �A�C�e���ڍ�", gm.colorWhite);
		SetFontSize(gm.DefaultFontSize_);
	}

	/*---------------*/

	/*-----�쐬����I�����`��-----*/
	else if (!recipeSelection_ && !MakeEnd_)
	{
		DrawGraph(NextButtonX_, NextButtonY_, gm.image.end, TRUE);

		DrawGraph(WindowX_, RecipeWindowX_, gm.image.recipeWindow, TRUE);

		for (int i = 0; i < canWeaponMake_.size(); i++)
		{
			if (canWeaponMake_[i])
			{
				DrawString(DrawWeaponName_LeftLine_X_, DrawWeaponName_Y_ + (CursorY_MoveVerticalWidth_RecipeSelect_ * i), weaponName_[i * 2].c_str(), gm.colorWhite);
				DrawString(DrawWeaponName_RightLine_X_, DrawWeaponName_Y_ + (CursorY_MoveVerticalWidth_RecipeSelect_ * i), weaponName_[i * 2 + 1].c_str(), gm.colorWhite);
			}
		}

		if (cursorX_ < CursorX_ProceedNextPart_)
			DrawGraph(cursorX_, cursorY_, gm.image.recipeSelection, TRUE);
		else
			DrawGraph(cursorX_, cursorY_, gm.image.nextCursor, TRUE);
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
		DrawBox(0, 0, Screen::width, Screen::height, gm.colorBrack, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, Screen::height / 2, drawMassege.c_str(), gm.colorWhite);
		drawMassege = "Z�L�[�Ŗ߂�";
		DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}

	/*-----�f�ޑI���㕐�퐶���A�j���[�V����-----*/
	if (MakeEnd_)
	{
		if (drawCounter_ > 0)
		{
			if (animationSoundTimer_ >= animationSoundTime_)
			{
				PlaySoundMem(Music::production_SE, DX_PLAYTYPE_BACK);
				animationSoundTimer_ = 0;
			}
			for (int i = 0; i < drawItemID_.size(); i++)
			{
				animationX_[i] = (Screen::width / 2) + cos((std::abs(angle_) / drawItemID_.size()) * (i + 1) * MyMath::Deg2Rad) * distToCenter_;
				animationY_[i] = (Screen::height / 2) + sin((std::abs(angle_) / drawItemID_.size()) * (i + 1) * MyMath::Deg2Rad) * distToCenter_;

				angle_ += 10;
			}

			for (int i = 0; i < drawItemID_.size(); i++)
				DrawGraph(animationX_[i], animationY_[i], gm.image.itemIcons[drawItemID_[i]], TRUE);

			distToCenter_--;
			drawCounter_--;
			animationSoundTimer_++;
		}
		else
		{
			if (!playProductionEndSound_)
			{
				PlaySoundMem(Music::productionend_SE, DX_PLAYTYPE_BACK);
				playProductionEndSound_ = true;
			}
			DrawGraph(Screen::width / 2, Screen::height / 2, gm.image.weaponIcons[weaponID_], TRUE);
			std::string drawMassege = "Z�L�[�Ŏ���";
			int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
			DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);

			if (Input::GetButtonDown(PAD_INPUT_1))
			{
				MakeEnd_ = false;
				animationEnd_ = true;
				playProductionEndSound_ = false;
				distToCenter_ = defaultDrawCount_;
				drawCounter_ = defaultDrawCount_;
				angle_ = defaultAngle_;
				animationX_.clear();
				animationY_.clear();
				drawItemID_.clear();
			}
		}
	}

	/*---------------*/

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


