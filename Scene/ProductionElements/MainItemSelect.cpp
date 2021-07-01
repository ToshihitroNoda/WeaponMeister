#include "MainItemSelect.h"
#include "../../MyLib/Input.h"
#include "../../Music.h"

void MainItemSelect::Update()
{
	if (Input::GetButtonDown(PAD_INPUT_1) || Input::GetKeyDown(KEY_INPUT_RETURN))
	{
		if (cursorX_ <= CursorX_Max_ItemSelect_ && !Input::GetKeyDown(KEY_INPUT_RETURN))
		{
			if (selectIconNum_ < itemForWeaponMake_.size())
			{
				PlaySoundMem(Music::enter_SE, DX_PLAYTYPE_BACK);
				if (gm.main.size() < MainSelect_MaxSize_ && !AlreadySecectItem(ItemPosOnThePouch_[selectIconNum_])) // �d�����Ă��Ȃ�������
				{
					addItem();
				}
				else
				{
					eraseItem();
				}
			}
		}
		else
		{
			allSelectEnd();
		}
	}

	if (Input::GetButtonDown(PAD_INPUT_2))
	{
		PlaySoundMem(Music::cancel_SE, DX_PLAYTYPE_BACK);
		shouldWeaponMainCreate_ = false;
		gm.main.clear();
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

	// �ڍ׃E�B���h�E�\�������܂܃J�[�\���ړ����Ă�����悤��
	if (itemForWeaponMake_.size() > 0 && selectIconNum_ >= itemForWeaponMake_.size())
		itemDetail_ = false;

	if (gm.main.size() > 1)
	{
		MainSlectOk_ = true;
	}
	else
	{
		MainSlectOk_ = false;
	}
}

void MainItemSelect::Draw()
{

	for (int i = 0; i < gm.main.size(); i++)
	{
		if (gm.main.size() > 0)
		{
			// �I���������̂�`��
			DrawGraph
			(AlreadySelect_MainItem_X_ + i * AlreadySelect_MainItem_X_Diameter_,
			 AlreadySelect_MainItem_Y_,
			 gm.image.itemIcons[gm.main.get_item_element(i)],
			 TRUE);
		}
	}
}

void MainItemSelect::addItem()
{
	gm.main.Add(itemForWeaponMake_[selectIconNum_], itemQualityForWeaponMake_[selectIconNum_]);
	SelectItemPosOnThePouch_.push_back(NowDrawPosOnPouch_[selectIconNum_ - scrollCount_ * WindowX_CellSize_]);
}

void MainItemSelect::eraseItem()
{
	for (int i = 0; i < gm.main.size(); i++)
	{
		if (SelectItemPosOnThePouch_[i + gm.handles.size()] == ItemPosOnThePouch_[selectIconNum_])
		{
			for (int j = 0; j < gm.handles.size(); j++)
			{
				if (SelectItemPosOnThePouch_[j] != NowDrawPosOnPouch_[selectIconNum_ - scrollCount_ * WindowX_CellSize_])
				{
					gm.main.EraseToBegin(i);
					SelectItemPosOnThePouch_.erase(SelectItemPosOnThePouch_.begin() + (i + gm.handles.size()));
					break;
				}
			}
		}
	}
}

void MainItemSelect::allSelectEnd()
{
	bool roopBreak = false;
	for (int i = 0; i < gm.handles.size(); i++)
	{
		for (int j = 0; j < gm.main.size(); j++)
		{   // ���C�������I����A�K�v�f�ނ��܂܂�Ă�����
			if (MainSlectOk_ &&
				((int)gm.weaponData[CsvNecessaryItem_][weaponID_ + CsvSkipCell_] == gm.handles.get_item_element(i) ||
					(int)gm.weaponData[CsvNecessaryItem_][weaponID_ + CsvSkipCell_] == gm.main.get_item_element(j)))
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
				weaponMakeAssert_ = true;
			}
		}
		if (roopBreak)
			break;
	}
}
